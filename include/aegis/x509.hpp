#ifndef AEGIS_X509_HPP
#define AEGIS_X509_HPP

#include <aegis/constants.hpp>
#include <aegis/memory.hpp>
#include <aegis/string.hpp>
#include <aegis/stack.hpp>

#include <openssl/x509.h>

namespace aegis {

template <> struct retain_traits<X509> {
  using reset_action = apex::adopt_t;
  static void increment (X509*) noexcept;
  static void decrement (X509*) noexcept;
};

} /* namespace aegis */

namespace aegis::io { struct stream; } /* namespace aegis::io */

namespace aegis::x509 {

struct certificate;
struct entry;
struct name;

struct certificate : private retain_handle<X509> {

  certificate (io::stream const&) noexcept;

  // TODO: use stack<ext::general_name> later
  stack<GENERAL_NAME> subject_alternative_names () const noexcept;
  name subject_name () const noexcept;

  using handle_type::handle_type;
  using handle_type::operator bool;
  using handle_type::get;
};

struct name : private view_handle<X509_NAME> {
  using size_type = std::size_t;

  entry operator [] (size_type) const noexcept;
  size_type find (extension, size_type) const noexcept;
  size_type find (extension) const noexcept;
  size_type size () const noexcept;

  using handle_type::handle_type;
  using handle_type::operator bool;
  using handle_type::get;
};

struct entry : private view_handle<X509_NAME_ENTRY> {

  string data () const noexcept;

  using handle_type::handle_type;
  using handle_type::operator bool;
  using handle_type::get;
};

} /* namespace aegis::x509 */

#endif /* AEGIS_X509_HPP */
