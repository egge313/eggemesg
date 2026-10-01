// ProtectedPage -- Store and retrieve data which is protected in the RAM
//               -- so that it is never swapped.
//               -- If the OS agrees, the data is never part of a sysdump.
//               -- Keep in mind that the super user can see pretty much
//               -- anything, though.
//               -- All of the code should be invoked within a try-catch
//               -- entrapment, since there is an abundance of std::error being
//               -- raised.
//
//               -- Originates from CoPilot, later modified and augmented
//               -- by Egge (esa.kettunen@gmx.com)
//
//               -- TODO: Convert to use unsigned char or bytes or similar. 

#pragma once

#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

class ProtectedPage
{
private:
    // Forbid copy constructor.
    ProtectedPage(ProtectedPage const &);

    // Forbid assignment operator.
    ProtectedPage& operator=(ProtectedPage const &);

public:

    ProtectedPage()
    {
        long page_size = ::sysconf(_SC_PAGESIZE);
	std::cout << "Page size is " << page_size << "\n";
        if (page_size <= 0)
	    {
		throw std::runtime_error("could not determine page size");
	    }

        m_pageSize = static_cast<std::size_t>(page_size);

        m_address = ::mmap(
			   nullptr,
			   m_pageSize,
			   PROT_WRITE | PROT_READ,
			   MAP_PRIVATE | MAP_ANONYMOUS | MAP_LOCKED,
			   -1,
			   0
			   );

        if (m_address == MAP_FAILED)
	    {
		throw std::runtime_error(
					 "mmap failed: " +
					 std::string(std::strerror(errno))
					 );
	    }

        struct rlimit limit {};
        if (::getrlimit(RLIMIT_MEMLOCK, &limit) == 0)
	    {
		std::cerr << "RLIMIT_MEMLOCK: soft=";

		if (limit.rlim_cur == RLIM_INFINITY) {
		    std::cerr << "unlimited";
		} else {
		    std::cerr << limit.rlim_cur << " bytes";
		}

		std::cerr << ", hard=";

		if (limit.rlim_max == RLIM_INFINITY) {
		    std::cerr << "unlimited";
		} else {
		    std::cerr << limit.rlim_max << " bytes";
		}

		std::cerr << '\n';
	    }

        if (::mlock(m_address, m_pageSize) != 0)
	    {
		int error = errno;
		::munmap(m_address, m_pageSize);
		m_address = nullptr;

		throw std::runtime_error(
					 "mlock failed: " +
					 std::string(std::strerror(error)) +
                           ". Increase RLIMIT_MEMLOCK or run without mlock."
					 );
	    }

        m_locked = true;

        // Optional: exclude this mapping from core dumps.
        ::madvise(m_address, m_pageSize, MADV_DONTDUMP);
    }

    int dowrite (const char* str, const unsigned length)
    {
	if (::munlock(m_address, m_pageSize) != 0) 
	    {
		int error = errno;
		::munmap(m_address, m_pageSize);
		m_address = nullptr;
		
		throw std::runtime_error(
					 "munlock failed: " +
					 std::string(std::strerror(error)) +
			      ". Increase RLIMIT_MEMLOCK or run without mlock."
					 );
	    }
	m_locked = false;
	{
	    volatile char* addrstr = static_cast<volatile char*>(m_address);

	    for (unsigned i = 0; i < length; i++)
		{
		    addrstr[i] = str[i];
		}
	}
	if (::mlock(m_address, m_pageSize) != 0) 
	    {
		int error = errno;
		::munmap(m_address, m_pageSize);
		m_address = nullptr;
		
		throw std::runtime_error(
					 "mlock failed: " +
					 std::string(std::strerror(error)) +
			      ". Increase RLIMIT_MEMLOCK or run without mlock."
					 );
	    }
	m_locked = true;
	return 0;
    }

    void doread (char *result, const unsigned length) 
    {
	if (::munlock(m_address, m_pageSize) != 0) 
	    {
		int error = errno;
		::munmap(m_address, m_pageSize);
		m_address = nullptr;
		
		throw std::runtime_error(
					 "munlock failed: " +
					 std::string(std::strerror(error)) +
			      ". Increase RLIMIT_MEMLOCK or run without mlock."
					 );
        }
	m_locked = false;

	{
	    char* addrstr = static_cast<char*>(m_address);
	    unsigned len = (unsigned)strlen(addrstr);
	    if (len > length)
		{
		    len = length;
		}
	    for (unsigned i = 0; i < len; i++)
		{
		    result[i] = addrstr[i];
		}
	}
	if (::mlock(m_address, m_pageSize) != 0) 
	    {
		int error = errno;
		::munmap(m_address, m_pageSize);
		m_address = nullptr;
		
		throw std::runtime_error(
					 "mlock failed: " +
					 std::string(std::strerror(error)) +
			      ". Increase RLIMIT_MEMLOCK or run without mlock."
					 );
	    }
	else
	    {
		m_locked = true;
	    }
    }


    ~ProtectedPage() {
        if (m_address && m_address != MAP_FAILED)
	    {
		// Clear the contents before releasing the mapping.
		if (::mprotect(m_address,
			       m_pageSize,
			       PROT_READ | PROT_WRITE) == 0)
		    {
			volatile unsigned char* p =
			    static_cast<volatile unsigned char*>(m_address);
			
			for (std::size_t i = 0; i < m_pageSize; ++i)
			    {
				p[i] = 0;
			    }
            }

            if (m_locked)
		{
		    ::munlock(m_address, m_pageSize);
		}

            ::munmap(m_address, m_pageSize);
        }
    }

private:
    void* m_address = nullptr;
    std::size_t m_pageSize = 0;
    bool m_locked = false;
};

#ifdef EGGEDEBUG

int main() {
    try
	{
	    char table[1024];
	    unsigned len = 1024;

	    ProtectedPage page;
	    std::cout << "Protected page created\n";
	    page.dowrite("EFG", 3);
	    page.doread((char *)table, len);
	    table[3] = '\0';
	    std::cout << "Read this:" << table << "\n";
	} 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}

#endif

