/*!
 * \file painter_header.hpp
 * \brief file painter_header.hpp
 *
 * Copyright 2016 by Intel.
 *
 * Contact: kevin.rogovin@intel.com
 *
 * This Source Code Form is subject to the
 * terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with
 * this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * \author Kevin Rogovin <kevin.rogovin@intel.com>
 *
 */
#pragma once

#include <fastuidraw/util/util.hpp>
#include <fastuidraw/util/vecN.hpp>
#include <fastuidraw/util/c_array.hpp>

namespace fastuidraw
{
/*!\addtogroup Painter
  @{
 */

  /*!
    A PainterHeader represents the values of the header for
    the shaders to read to draw data. The header holds data
    that is common for all vertices and fragments for an
    item to draw, including with what shader and the data
    for the shader.
   */
  class PainterHeader
  {
  public:
    /*!
      Bit packing for the z-blend-shader field of the header
      (located at z_blend_shader_offset)
     */
    enum z_blend_shader_encoding
      {
       /*!
          Number of bits used for the z-value
         */
        z_num_bits = 23,

        /*!
          Number of bits used for the blend shader ID
         */
        blend_shader_num_bits = 32 - z_num_bits,

        /*!
          First bit used to store the z value
         */
        z_bit0 = 0,

        /*!
          First bit used to store the blend shader ID
         */
        blend_shader_bit0 = z_num_bits,
      };

    /*!
      Enumerations specifying how the contents of a PainterHeader
      are packed into a data store buffer (PainterDrawCommand::m_store).
     */
    enum offset_t
      {
        clip_equations_location_offset, /*!< offset to \ref m_clip_equations_location */
        item_matrix_location_offset, /*!< offset to \ref m_item_matrix_location */
        brush_shader_data_location_offset, /*!< offset to \ref m_brush_shader_data_location */
        item_shader_data_location_offset, /*!< offset to \ref m_item_shader_data_location */
        blend_shader_data_location_offset, /*!< offset to \ref m_blend_shader_data_location */
        item_shader_offset, /*!< offset to \ref m_item_shader */
        brush_shader_offset, /*!< offset to \ref m_brush_shader */
        z_blend_shader_offset, /*!< offset to \ref m_blend_shader and m_z packed into single 32-bit value */

        header_size /*!< size of header */
      };

    /*!
      The offset, in units of PainterBackend::Configuration::alignment()
      generic_data tuples, to the location in the data store buffer
      (PainterDrawCommand::m_store) for the clip equations. I.e.
      the PainterClipEquations value is stored (packed) at the location
      \code
      PainterDrawCommand::m_store[m_clip_equations_location * PainterBackend::Configuration::alignment()]
      \endcode
     */
    uint32_t m_clip_equations_location;

    /*!
      The location, in units of PainterBackend::Configuration::alignment()
      generic_data tuples, to the location in the data store buffer
      (PainterDrawCommand::m_store) for the item matrix. I.e.
      the PainterItemMatrix value is stored (packed) at the location
      \code
      PainterDrawCommand::m_store[m_item_matrix_location * PainterBackend::Configuration::alignment()]
      \endcode
     */
    uint32_t m_item_matrix_location;

    /*!
      The location, in units of PainterBackend::Configuration::alignment()
      generic_data tuples, to the location in the data store buffer
      (PainterDrawCommand::m_store) for the brush shader data. I.e.
      the data for a brush is stored (packed) at the location
      \code
      PainterDrawCommand::m_store[m_brush_shader_data_location * PainterBackend::Configuration::alignment()]
      \endcode
     */
    uint32_t m_brush_shader_data_location;

    /*!
      The location, in units of PainterBackend::Configuration::alignment()
      generic_data tuples, to the location in the data store buffer
      (PainterDrawCommand::m_store) for the item shader data. I.e.
      the PainterItemShaderData value is stored (packed) at the location
      \code
      PainterDrawCommand::m_store[m_item_shader_data_location * PainterBackend::Configuration::alignment()]
      \endcode
     */
    uint32_t m_item_shader_data_location;

    /*!
      The location, in units of PainterBackend::Configuration::alignment()
      generic_data tuples, to the location in the data store buffer
      (PainterDrawCommand::m_store) for the item shader data. I.e.
      the PainterBlendShaderData value is stored (packed) at the location
      \code
      PainterDrawCommand::m_store[m_blend_shader_data_location * PainterBackend::Configuration::alignment()]
      \endcode
     */
    uint32_t m_blend_shader_data_location;

    /*!
      The ID of the item shader (i.e. PainterItemShader::ID()).
     */
    uint32_t m_item_shader;

    /*!
      The brush shader, i.e. the value of PainterBrush::shader().
     */
    uint32_t m_brush_shader;

    /*!
      The ID of the blend shader (i.e. PainterBlendShader::ID()).
     */
    uint32_t m_blend_shader;

    /*!
      The z-value to use for the item. The z-value is used
      by Painter to implement clipping.
     */
    uint32_t m_z;

    /*!
      Pack the values of this PainterHeader
      \param alignment alignment of the data store
      in units of generic_data, see
      PainterBackend::ConfigurationBase::alignment()
      \param dst place to which to pack data
    */
    void
    pack_data(c_array<generic_data> dst) const;
  };

/*! @} */
}
