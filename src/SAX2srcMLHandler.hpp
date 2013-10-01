/*
  @file SAX2srcMLHandler.hpp

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

#ifndef INCLUDED_SAX2SRCMLHANDLER_HPP
#define INCLUDED_SAX2SRCMLHANDLER_HPP

#include <srcMLHandler.hpp>

#include <libxml/parser.h>

/**
 * Element
 *
 * Data structure to hold an element
 * mainly root lement
 */
struct Element {

  const xmlChar* localname;
  const xmlChar* prefix;
  const xmlChar* URI;
  int nb_namespaces;
  const xmlChar** namespaces;
  int nb_attributes;
  int nb_defaulted;
  const xmlChar** attributes;

};

/**
 * SAX2srcMLHandler
 *
 * Data structure to hold process during
 * sax parsing.
 */
struct SAX2srcMLHandler {

  /** Hooks for processing */
  srcMLHandler * process;

  /** Temporary storage for root unit */
  Element root;

};

/**
 * factory
 *
 * Create SAX handler.
 */
xmlSAXHandler factory();

/**
 * startDocument
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for start of document.
 * Immediately calls supplied handlers function.
 */
void startDocument(void * ctx);

/**
 * endDocument
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for end of document.
 * Immediately calls supplied handlers function.
 */
void endDocument(void * ctx);

/**
 * startElementNs
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of an element.
 * Immediately calls supplied handlers function.
 */
void startElementNs(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                           int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                           const xmlChar ** attributes);

/**
 * endElementNs
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 *
 * SAX handler function for end of an element.
 * Immediately calls supplied handlers function.
 */
void endElementNs(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI);

/**
 * characters
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling.
 * Immediately calls supplied handlers function.
 */
void characters(void * ctx, const xmlChar * ch, int len);

#endif
