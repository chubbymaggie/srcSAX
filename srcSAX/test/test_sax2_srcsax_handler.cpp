/**
 * @file test_sax2_srcsax_handler.cpp
 *
 * @copyright Copyright (C) 2013-2014  SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <sax2_srcsax_handler.hpp>
#include <srcsax_handler_test.hpp>

#include <srcsax.h>

#include <stdio.h>
#include <string.h>
#include <cassert>

/* default initialization used throughout for testing */
sax2_srcsax_handler sax2_handler_init;

/**
 * main
 *
 * Test the sax2_srcsax_handler.
 *
 * @returns 0 on success.
 */
int main() {

  /*
    start_document
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    start_document(&ctxt);

  }

  {

    start_document(NULL);

  }

  /*
    end_document
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    end_document(&ctxt);

  }

  {

    end_document(NULL);

  }

  /*
    start_root
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                   "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };
    start_root(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);

    assert((const char *)sax2_handler.root.localname == std::string("unit"));
    assert((const char *)sax2_handler.root.prefix == std::string("src"));
    assert((const char *)sax2_handler.root.URI == std::string("http://www.sdml.info/srcML/src"));
    assert(sax2_handler.root.nb_namespaces == 2);
    assert((const char *)sax2_handler.root.namespaces[0] == std::string("src"));
    assert((const char *)sax2_handler.root.namespaces[1] == std::string("http://www.sdml.info/srcML/src"));
    assert((const char *)sax2_handler.root.namespaces[2] == std::string("cpp"));
    assert((const char *)sax2_handler.root.namespaces[3] == std::string("http://www.sdml.info/srcML/cpp"));
    assert(sax2_handler.root.nb_attributes == 3);
    assert(sax2_handler.root.nb_defaulted == 0);
    assert((const char *)sax2_handler.root.attributes[0] == std::string("filename"));
    assert((const char *)sax2_handler.root.attributes[1] == std::string("src"));
    assert((const char *)sax2_handler.root.attributes[2] == std::string("http://www.sdml.info/srcML/src"));
    assert(sax2_handler.root.attributes[4] - sax2_handler.root.attributes[3] == 1);
    assert((char)sax2_handler.root.attributes[3][0] == 'a');
    assert((const char *)sax2_handler.root.attributes[5] == std::string("dir"));
    assert((const char *)sax2_handler.root.attributes[6] == std::string("src"));
    assert((const char *)sax2_handler.root.attributes[7] == std::string("http://www.sdml.info/srcML/src"));
    assert(sax2_handler.root.attributes[9] - sax2_handler.root.attributes[8] == 1);
    assert((char)sax2_handler.root.attributes[8][0] == 'b');
    assert((const char *)sax2_handler.root.attributes[10] == std::string("language"));
    assert((const char *)sax2_handler.root.attributes[11] == std::string("src"));
    assert((const char *)sax2_handler.root.attributes[12] == std::string("http://www.sdml.info/srcML/src"));
    assert(sax2_handler.root.attributes[14] - sax2_handler.root.attributes[13] == 1);
    assert((char)sax2_handler.root.attributes[13][0] == 'c');
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_element_ns_first);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
    end_document(&ctxt);

  }

  {

    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                    "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };
    start_root(NULL, (const xmlChar *)"unit", (const xmlChar *)"src",
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);

  }


  /*
    start_element_ns_first
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                   "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };

    start_element_ns_first(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_element_ns);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_unit);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                    "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };
    start_element_ns_first(NULL, (const xmlChar *)"unit", (const xmlChar *)"src",
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);

  }

  /*
    start_unit
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                   "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };

    start_unit(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_element_ns);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_unit);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {

    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                    "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };
    start_unit(NULL, (const xmlChar *)"unit", (const xmlChar *)"src",
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);

  }

  /*
    start_element_ns
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                   "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };

    start_element_ns(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {
    const char * namespaces[4] = { "src", "http://www.sdml.info/srcML/src", "cpp", "http://www.sdml.info/srcML/cpp" };
    const char * values = "abc";
    const char * attributes[15] = { "filename", "src", "http://www.sdml.info/srcML/src", values, values + 1,
                                    "dir", "src", "http://www.sdml.info/srcML/src", values + 1, values + 2,
                                    "language", "src", "http://www.sdml.info/srcML/src", values + 2, values + 3 };
    start_element_ns(NULL, (const xmlChar *)"unit", (const xmlChar *)"src",
              (const xmlChar *)"http://www.sdml.info/srcML/src", 2, (const xmlChar **)namespaces, 3, 0,
              (const xmlChar **) attributes);

  }

  /*
    end_element_ns
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    end_element_ns(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
                   (const xmlChar *)"http://www.sdml.info/srcML/src");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_unit);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_root);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    sax.startElementNs = &start_unit;
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    end_element_ns(&ctxt, (const xmlChar *)"unit", (const xmlChar *)"src", 
                   (const xmlChar *)"http://www.sdml.info/srcML/src");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_unit);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    end_element_ns(&ctxt, (const xmlChar *)"name", (const xmlChar *)"src", 
                   (const xmlChar *)"http://www.sdml.info/srcML/src");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {

    end_element_ns(NULL, (const xmlChar *)"unit", (const xmlChar *)"src",
                 (const xmlChar *)"http://www.sdml.info/srcML/src");
  }

  /*
    characters_first
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    characters_first(&ctxt, (const xmlChar *)"unit", 4);
    assert(sax2_handler.characters == "unit");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);

  }

  {

    characters_first(NULL, (const xmlChar *)"unit", 4);

  }

  /*
    characters_root
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    characters_root(&ctxt, (const xmlChar *)"unit", 4);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
  }

  {

    characters_root(NULL, (const xmlChar *)"unit", 4);

  }

  /*
    characters_unit
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    characters_unit(&ctxt, (const xmlChar *)"unit", 4);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
  }

  {

    characters_unit(NULL, (const xmlChar *)"unit", 4);

  }

  /*
    comment
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    comment(&ctxt, (const xmlChar *)"unit");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
  }

  {

    comment(NULL, (const xmlChar *)"unit");

  }

  /*
    cdata_block
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    cdata_block(&ctxt, (const xmlChar *)"unit", 4);
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
  }

  {

    cdata_block(NULL, (const xmlChar *)"unit", 4);

  }

  /*
    processing_instruction
   */
  {

    srcsax_handler_test test_handler;
    srcsax_handler srcsax_sax = srcsax_handler_test::factory();

    srcsax_context context;
    context.data = &test_handler;
    context.handler = &srcsax_sax;

    sax2_srcsax_handler sax2_handler = sax2_handler_init;
    sax2_handler.context = &context;

    xmlParserCtxt ctxt;
    xmlSAXHandler sax = srcsax_sax2_factory();
    ctxt.sax = &sax;
    ctxt._private = &sax2_handler;
    processing_instruction(&ctxt, (const xmlChar *)"target", (const xmlChar *)"data");
    assert(ctxt.sax->startDocument == start_document);
    assert(ctxt.sax->endDocument == end_document);
    assert(ctxt.sax->startElementNs == start_root);
    assert(ctxt.sax->endElementNs == end_element_ns);
    assert(ctxt.sax->characters == characters_first);
    assert(ctxt.sax->comment == comment);
    assert(ctxt.sax->cdataBlock == cdata_block);
    assert(ctxt.sax->processingInstruction == processing_instruction);
  }

  {

    processing_instruction(NULL, (const xmlChar *)"target", (const xmlChar *)"data");

  }

  return 0;
}
