/*
  @file srcMLControlHandler.hpp

  Copyright (C) 2004-2013  SDML (www.sdml.info)

  This file is part of the srcML SAX2 Framework.

  The srcML SAX2 Framework is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML SAX2 Framework is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML SAX2 Framework; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef INCLUDED_SRCMLCONTROLHANDLER_HPP
#define INCLUDED_SRCMLCONTROLHANDLER_HPP

#include <srcMLHandler.hpp>
#include <SAX2srcMLHandler.hpp>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>

/**
 * srcMLControlHandler
 *
 * Provides execution of sax with
 * given hooks.
 */
class srcMLControlHandler {

private :

  // xmlParserCtxt
  xmlParserCtxtPtr ctxt;

  // xmlSAXHandler
  xmlSAXHandler sax;

  // Process to execute call backs
  SAX2srcMLHandler sax2_handler;

public :

  /**
   * srcMLControlHandler
   * @param filename name of a file
   *
   * Constructor
   */
  srcMLControlHandler(const char * filename);

  /**
   * ~srcMLControlHandler
   *
   * Constructor
   */
  ~srcMLControlHandler();

  void enable_startDocument(bool enable);
  void enable_endDocument(bool enable);
  void enable_startElementNs(bool enable);
  void enable_endElementNs(bool enable);
  void enable_characters(bool enable);

  /**
   * parse
   * @param handler srcMLHandler with hooks for sax parsing
   *
   * Parse the xml document with the supplied hooks.
   */
  void parse(srcMLHandler * handler);

};

#endif
