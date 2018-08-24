/*
 * whatsapp.c
 *
 * =========================================================================
 *  Copyright (C) 2012-2013, Daniele De Sensi (d.desensi.software@gmail.com)
 *
 *  This file is part of Peafowl.
 *
 *  Peafowl is free software: you can redistribute it and/or
 *  modify it under the terms of the Lesser GNU General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.

 *  Peafowl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Lesser GNU General Public License for more details.
 *
 *  You should have received a copy of the Lesser GNU General Public
 *  License along with Peafowl.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 * =========================================================================
 */
#include <peafowl/peafowl.h>
#include <peafowl/inspectors/inspectors.h>

static uint8_t whatsapp_sequence[] = {
    0x45, 0x44, 0x0, 0x01, 0x0, 0x0, 0x02, 0x08,
    0x0, 0x57, 0x41, 0x02, 0x0, 0x0, 0x0
 };

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

uint8_t check_whatsapp(dpi_library_state_t* state, dpi_pkt_infos_t* pkt,
                      const unsigned char* app_data, uint32_t data_length,
                      dpi_tracking_informations_t* t){
  if(t->whatsapp_matched_sequence < sizeof(whatsapp_sequence)) {
    if(memcmp(app_data, &whatsapp_sequence[t->whatsapp_matched_sequence], 
      MIN(sizeof(whatsapp_sequence) - t->whatsapp_matched_sequence, data_length))) {
      return DPI_PROTOCOL_NO_MATCHES;
    } else {
      t->whatsapp_matched_sequence += data_length;
      return DPI_PROTOCOL_MORE_DATA_NEEDED;
    }
  } else {
    return DPI_PROTOCOL_MATCHES;
  }
}