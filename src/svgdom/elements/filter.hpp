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

#include <array>

#include <r4/vector.hpp>

#include "container.hpp"
#include "coordinate_units.hpp"
#include "element.hpp"
#include "rectangle.hpp"
#include "referencing.hpp"
#include "styleable.hpp"

namespace svgdom {

using namespace std::string_view_literals;

struct filter_element : public element, public styleable, public rectangle, public referencing, public container {
	constexpr static auto default_filter_region_x = -10;
	constexpr static auto default_filter_region_y = -10;
	constexpr static auto default_filter_region_width = 120;
	constexpr static auto default_filter_region_height = 120;

	coordinate_units filter_units = coordinate_units::object_bounding_box;
	coordinate_units primitive_units = coordinate_units::user_space_on_use;

	// NOTE: filterRes attribute is dropped, it seems deprecated.

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	std::string_view get_id() const override
	{
		return this->id;
	}

	constexpr static std::string_view tag = "filter"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

struct filter_primitive : public element, public rectangle, public styleable {
	std::string result;

	std::string_view get_id() const override
	{
		return this->id;
	}
};

// TODO: why lint complains here on macos?
// NOLINTNEXTLINE(bugprone-exception-escape, "error: an exception may be thrown in function")
struct inputable {
	std::string in;
};

// TODO: why lint complains here on macos?
// NOLINTNEXTLINE(bugprone-exception-escape, "error: an exception may be thrown in function")
struct second_inputable {
	std::string in2;
};

struct fe_gaussian_blur_element : public filter_primitive, public inputable {
	r4::vector2<real> std_deviation = -1;

	/**
	 * @brief Tells if stdDeviation attribute is specified in XML.
	 * @return true if stdDeviation attribute is specified in XML.
	 * @return false otherwise.
	 */
	bool is_std_deviation_specified() const noexcept
	{
		return this->std_deviation[0] >= 0;
	}

	/**
	 * @brief Tells if two numbers are specified for stdDeviation attribute.
	 * @return true if two numbers are specified for stdDeviation attribute in XML.
	 * @return false otherwise.
	 */
	bool is_std_deviation_y_specified() const noexcept
	{
		return this->std_deviation[1] >= 0;
	}

	r4::vector2<real> get_std_deviation() const noexcept;

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	constexpr static std::string_view tag = "feGaussianBlur"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
struct fe_color_matrix_element : public filter_primitive, public inputable {
	enum class type {
		matrix,
		saturate,
		hue_rotate,
		luminance_to_alpha
	};

	type type_ = type::matrix;

	constexpr static auto max_num_values = 20;

	std::array<real, max_num_values> values;

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	constexpr static std::string_view tag = "feColorMatrix"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

struct fe_blend_element : public filter_primitive, public inputable, public second_inputable {
	enum class mode {
		normal,
		multiply,
		screen,
		darken,
		lighten
	} mode_ = mode::normal;

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	constexpr static std::string_view tag = "feBlend"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
struct fe_composite_element : public filter_primitive, public inputable, public second_inputable {
	enum class operator_type {
		over,
		in,
		out,
		atop,
		xor_operator,
		arithmetic
	} operator_attribute = operator_type::over;

	real k1, k2, k3, k4;

	void accept(visitor& v) override;
	void accept(const_visitor& v) const override;

	constexpr static std::string_view tag = "feComposite"sv;

	std::string_view get_tag() const override
	{
		return tag;
	}
};

} // namespace svgdom
