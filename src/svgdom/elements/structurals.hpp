/*
The MIT License (MIT)

Copyright (c) 2015-2025 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/* ================ LICENSE END ================ */

#pragma once

#include "aspect_ratioed.hpp"
#include "container.hpp"
#include "coordinate_units.hpp"
#include "element.hpp"
#include "rectangle.hpp"
#include "referencing.hpp"
#include "styleable.hpp"
#include "transformable.hpp"
#include "view_boxed.hpp"

namespace svgdom {

using namespace std::string_view_literals;

// TODO: why lint complains here on macos?
// NOLINTNEXTLINE(bugprone-exception-escape, "error: an exception may be thrown in function")
struct g_element : public element, public container, public transformable, public styleable {
	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "g"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

// TODO: why lint complains here on macos?
// NOLINTNEXTLINE(bugprone-exception-escape, "error: an exception may be thrown in function")
struct defs_element : public element, public container, public transformable, public styleable {
	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "defs"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

struct use_element : public element, public transformable, public referencing, public rectangle, public styleable {
	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "use"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

struct svg_element :
	public element,
	public container,
	public rectangle,
	public view_boxed,
	public aspect_ratioed,
	public styleable {
	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "svg"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}

	/**
	 * @brief Get aspect ratio of the element.
	 * @param dpi - dots per inch.
	 * @return aspect ratio of the element.
	 * @return 0 if any of height or weight is specified in percent.
	 */
	real aspect_ratio(real dpi) const;

	/**
	 * @brief Get natural dimensions in pixels.
	 * If any of the dimensions cannot be converted to pixels, e.g. because specified in percentage,
	 * then this dimensions will be returned as zero.
	 * @param dpi - dots per inch to use when converting lengths to pixels.
	 * @return dimensions in pixels.
	 */
	r4::vector2<real> get_dimensions(real dpi) const noexcept;
};

// TODO: why lint complains here on macos?
// NOLINTNEXTLINE(bugprone-exception-escape, "error: an exception may be thrown in function")
struct symbol_element : public element, public container, public view_boxed, public aspect_ratioed, public styleable {
	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "symbol"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

struct mask_element : public element, public container, public rectangle, public styleable {
	coordinate_units mask_units = coordinate_units::unknown;

	coordinate_units mask_content_units = coordinate_units::unknown;

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "mask"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

} // namespace svgdom
