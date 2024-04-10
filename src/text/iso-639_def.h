/*****************************************************************************
 * iso-639_def.h: language codes and abbreviations
 *****************************************************************************
 * Copyright (C) 1998-2004 VLC authors and VideoLAN
 *
 * Definitions taken from GNU glibc.
 *
 * Authors: Stéphane Borel <stef@via.ecp.fr>
 *          Arnaud de Bossoreille de Ribou <bozo@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/* This table defines ISO-639-1, ISO-639-2T and ISO-639-2B languages codes and
 * their mappings to descriptive labels.
 *
 * The entries have been copied in bulk from the set defined in glibc, with
 * minimal adjustments. Corrections or additions, unless they pertain to custom
 * VLC adjustments, should generally be discussed with the glibc developers,
 * then updated here subsequently if accepted by glibc.
 *
 * The glibc ordering should be preserved to avoid making future bulk updates
 * harder. (Rare VLC additions belong at the end).
 */

#define LANG_CODE(a,b,c,d) { a,  b, c,  d },
#define LANG_CODE2(a,c)    { a, "", c, "" }, /* two param version (ISO-639-2/T only) */
#define LANG_CODE3(a,c,d)  { a, "", c,  d }, /* three param version (ISO-639-2/T&B only) */

static const iso639_lang_t p_languages[] =
{
<<<<<<< HEAD
    /* Definitions taken from GNU glibc */
    LANG_CODE  ( N_("Abkhazian"),                                         "ab", "abk", "abk" )
    LANG_CODE3 ( N_("Achinese"),                                                "ace", "ace" )
    LANG_CODE3 ( N_("Acoli"),                                                   "ach", "ach" )
    LANG_CODE3 ( N_("Adangme"),                                                 "ada", "ada" )
    LANG_CODE3 ( N_("Adyghe; Adygei"),                                          "ady", "ady" )
    LANG_CODE  ( N_("Afar"),                                              "aa", "aar", "aar" )
    LANG_CODE3 ( N_("Afrihili"),                                                "afh", "afh" )
    LANG_CODE  ( N_("Afrikaans"),                                         "af", "afr", "afr" )
    LANG_CODE3 ( N_("Afro-Asiatic (Other)"),                                    "afa", "afa" )
    LANG_CODE3 ( N_("Ainu"),                                                    "ain", "ain" )
    LANG_CODE  ( N_("Akan"),                                              "ak", "aka", "aka" )
    LANG_CODE3 ( N_("Akkadian"),                                                "akk", "akk" )
    LANG_CODE  ( N_("Albanian"),                                          "sq", "sqi", "alb" )
    LANG_CODE3 ( N_("Aleut"),                                                   "ale", "ale" )
    LANG_CODE3 ( N_("Algonquian languages"),                                    "alg", "alg" )
    LANG_CODE3 ( N_("Southern Altai"),                                          "alt", "alt" )
    LANG_CODE3 ( N_("Altaic (Other)"),                                          "tut", "tut" )
    LANG_CODE  ( N_("Amharic"),                                           "am", "amh", "amh" )
    LANG_CODE3 ( N_("Angika"),                                                  "anp", "anp" )
    LANG_CODE3 ( N_("Apache languages"),                                        "apa", "apa" )
    LANG_CODE  ( N_("Arabic"),                                            "ar", "ara", "ara" )
    LANG_CODE  ( N_("Aragonese"),                                         "an", "arg", "arg" )
    LANG_CODE3 ( N_("Aramaic"),                                                 "arc", "arc" )
    LANG_CODE3 ( N_("Arapaho"),                                                 "arp", "arp" )
    LANG_CODE3 ( N_("Araucanian"),                                              "arn", "arn" )
    LANG_CODE3 ( N_("Arawak"),                                                  "arw", "arw" )
    LANG_CODE  ( N_("Armenian"),                                          "hy", "hye", "arm" )
    LANG_CODE3 ( N_("Aromanian; Arumanian; Macedo-Romanian"),                   "rup", "rup" )
  /*LANG_CODE3 ( N_("Artificial (Other)"),                                      "art", "art" )*/
    LANG_CODE  ( N_("Assamese"),                                          "as", "asm", "asm" )
    LANG_CODE3 ( N_("Asturian; Bable"),                                         "ast", "ast" )
    LANG_CODE3 ( N_("Athapascan languages"),                                    "ath", "ath" )
    LANG_CODE3 ( N_("Australian languages"),                                    "aus", "aus" )
    LANG_CODE3 ( N_("Austronesian (Other)"),                                    "map", "map" )
    LANG_CODE  ( N_("Avaric"),                                            "av", "ava", "ava" )
    LANG_CODE  ( N_("Avestan"),                                           "ae", "ave", "ave" )
    LANG_CODE3 ( N_("Awadhi"),                                                  "awa", "awa" )
    LANG_CODE3 ( N_("Aguaruna"),                                                "agr", "agr" )
    LANG_CODE  ( N_("Aymara, Southern"),                                  "ay", "ayc", "ayc" )
    LANG_CODE  ( N_("Aymara"),                                            "ay", "aym", "aym" )
    LANG_CODE  ( N_("Azerbaijani"),                                       "az", "aze", "aze" )
    LANG_CODE  ( N_("North Azerbaijani"),                                 "az", "azj", "aze" )
    LANG_CODE  ( N_("South Azerbaijani"),                                 "az", "azb", "aze" )
    LANG_CODE3 ( N_("Balinese"),                                                "ban", "ban" )
    LANG_CODE3 ( N_("Baltic (Other)"),                                          "bat", "bat" )
    LANG_CODE3 ( N_("Baluchi"),                                                 "bal", "bal" )
    LANG_CODE  ( N_("Bambara"),                                           "bm", "bam", "bam" )
    LANG_CODE3 ( N_("Bamileke languages"),                                      "bai", "bai" )
    LANG_CODE3 ( N_("Banda"),                                                   "bad", "bad" )
    LANG_CODE3 ( N_("Bantu (Other)"),                                           "bnt", "bnt" )
    LANG_CODE3 ( N_("Basa"),                                                    "bas", "bas" )
    LANG_CODE  ( N_("Bashkir"),                                           "ba", "bak", "bak" )
    LANG_CODE  ( N_("Basque"),                                            "eu", "eus", "baq" )
    LANG_CODE3 ( N_("Batak (Indonesia)"),                                       "btk", "btk" )
    LANG_CODE3 ( N_("Beja"),                                                    "bej", "bej" )
    LANG_CODE  ( N_("Belarusian"),                                        "be", "bel", "bel" )
    LANG_CODE3 ( N_("Bemba"),                                                   "bem", "bem" )
    LANG_CODE  ( N_("Bangla"),                                            "bn", "ben", "ben" )
    LANG_CODE3 ( N_("Berber (Other)"),                                          "ber", "ber" )
    LANG_CODE3 ( N_("Bhili"),                                                   "bhb", "bhb" )
    LANG_CODE3 ( N_("Bhojpuri"),                                                "bho", "bho" )
    LANG_CODE  ( N_("Bihari"),                                            "bh", "bih", "bih" )
    LANG_CODE3 ( N_("Bikol"),                                                   "bik", "bik" )
    LANG_CODE3 ( N_("Bini"),                                                    "bin", "bin" )
    LANG_CODE  ( N_("Bislama"),                                           "bi", "bis", "bis" )
    LANG_CODE3 ( N_("Blin; Bilin"),                                             "byn", "byn" )
    LANG_CODE3 ( N_("Bodo"),                                                    "brx", "brx" )
    LANG_CODE  ( N_("Bosnian"),                                           "bs", "bos", "bos" )
    LANG_CODE3 ( N_("Braj"),                                                    "bra", "bra" )
    LANG_CODE  ( N_("Breton"),                                            "br", "bre", "bre" )
    LANG_CODE3 ( N_("Buginese"),                                                "bug", "bug" )
    LANG_CODE  ( N_("Bulgarian"),                                         "bg", "bul", "bul" )
    LANG_CODE3 ( N_("Buriat"),                                                  "bua", "bua" )
    LANG_CODE  ( N_("Burmese"),                                           "my", "mya", "bur" )
    LANG_CODE3 ( N_("Caddo"),                                                   "cad", "cad" )
    LANG_CODE3 ( N_("Carib"),                                                   "car", "car" )
    LANG_CODE  ( N_("Catalan; Valencian"),                                "ca", "cat", "cat" )
    LANG_CODE3 ( N_("Caucasian (Other)"),                                       "cau", "cau" )
    LANG_CODE3 ( N_("Cebuano"),                                                 "ceb", "ceb" )
    LANG_CODE3 ( N_("Celtic (Other)"),                                          "cel", "cel" )
    LANG_CODE3 ( N_("Central American Indian (Other)"),                         "cai", "cai" )
    LANG_CODE3 ( N_("Central Nahuatl"),                                         "nhn", "nhn" )
    LANG_CODE3 ( N_("Central Sama"),                                            "sml", "sml" )
    LANG_CODE3 ( N_("Chagatai"),                                                "chg", "chg" )
    LANG_CODE3 ( N_("Chamic languages"),                                        "cmc", "cmc" )
    LANG_CODE  ( N_("Chamorro"),                                          "ch", "cha", "cha" )
    LANG_CODE  ( N_("Chechen"),                                           "ce", "che", "che" )
    LANG_CODE3 ( N_("Cherokee"),                                                "chr", "chr" )
    LANG_CODE3 ( N_("Cheyenne"),                                                "chy", "chy" )
    LANG_CODE2 ( N_("Chhattisgarhi"),                                           "hne"        )
    LANG_CODE3 ( N_("Chibcha"),                                                 "chb", "chb" )
    LANG_CODE  ( N_("Chichewa; Chewa; Nyanja"),                           "ny", "nya", "nya" )
    LANG_CODE3 ( N_("Chiga"),                                                   "cgg", "cgg" )
    LANG_CODE  ( N_("Chinese"),                                           "zh", "zho", "chi" )
    LANG_CODE3 ( N_("Chinook jargon"),                                          "chn", "chn" )
    LANG_CODE3 ( N_("Chipewyan"),                                               "chp", "chp" )
    LANG_CODE3 ( N_("Choctaw"),                                                 "cho", "cho" )
    LANG_CODE  ( N_("Church Slavic; Church Slavonic"),                    "cu", "chu", "chu" ) /* note: simplified label */
    LANG_CODE3 ( N_("Chuukese"),                                                "chk", "chk" )
    LANG_CODE  ( N_("Chuvash"),                                           "cv", "chv", "chv" )
  /*LANG_CODE3 ( N_("Classical Newari; Old Newari; Classical Nepal Bhasa"),     "nwc", "nwc" )*/
    LANG_CODE3 ( N_("Coptic"),                                                  "cop", "cop" )
    LANG_CODE  ( N_("Cornish"),                                           "kw", "cor", "cor" )
    LANG_CODE  ( N_("Corsican"),                                          "co", "cos", "cos" )
    LANG_CODE3 ( N_("Creek"),                                                   "mus", "mus" )
    LANG_CODE  ( N_("Cree"),                                              "cr", "cre", "cre" )
    LANG_CODE3 ( N_("Creoles and pidgins (Other)"),                             "crp", "crp" )
    LANG_CODE3 ( N_("Creoles and pidgins, English based (Other)"),              "cpe", "cpe" )
    LANG_CODE3 ( N_("Creoles and pidgins, French-based (Other)"),               "cpf", "cpf" )
    LANG_CODE3 ( N_("Creoles and pidgins, Portuguese-based (Other)"),           "cpp", "cpp" )
    LANG_CODE3 ( N_("Crimean Tatar; Crimean Turkish"),                          "crh", "crh" )
    LANG_CODE  ( N_("Croatian"),                                          "hr", "hrv", "scr" )
    LANG_CODE3 ( N_("Cushitic (Other)"),                                        "cus", "cus" )
    LANG_CODE  ( N_("Czech"),                                             "cs", "ces", "cze" )
    LANG_CODE3 ( N_("Dakota"),                                                  "dak", "dak" )
    LANG_CODE  ( N_("Danish"),                                            "da", "dan", "dan" )
    LANG_CODE3 ( N_("Dargwa"),                                                  "dar", "dar" )
    LANG_CODE3 ( N_("Dayak"),                                                   "day", "day" )
    LANG_CODE3 ( N_("Delaware"),                                                "del", "del" )
    LANG_CODE3 ( N_("Dinka"),                                                   "din", "din" )
    LANG_CODE  ( N_("Divehi"),                                            "dv", "div", "div" )
    LANG_CODE3 ( N_("Dogrib"),                                                  "dgr", "dgr" )
    LANG_CODE3 ( N_("Dogri"),                                                   "doi", "doi" )
    LANG_CODE3 ( N_("Dravidian (Other)"),                                       "dra", "dra" )
    LANG_CODE3 ( N_("Duala"),                                                   "dua", "dua" )
  /*LANG_CODE3 ( N_("Dutch, Middle (ca.1050-1350)"),                            "dum", "dum" )*/
    LANG_CODE  ( N_("Dutch; Flemish"),                                    "nl", "nld", "dut" )
    LANG_CODE3 ( N_("Dyula"),                                                   "dyu", "dyu" )
    LANG_CODE  ( N_("Dzongkha"),                                          "dz", "dzo", "dzo" )
    LANG_CODE3 ( N_("Efik"),                                                    "efi", "efi" )
  /*LANG_CODE3 ( N_("Egyptian (Ancient)"),                                      "egy", "egy" )*/
    LANG_CODE3 ( N_("Ekajuk"),                                                  "eka", "eka" )
    LANG_CODE3 ( N_("Elamite"),                                                 "elx", "elx" )
  /*LANG_CODE3 ( N_("English, Middle (1100-1500)"),                             "enm", "enm" )*/
  /*LANG_CODE3 ( N_("English, Old (ca.450-1100)"),                              "ang", "ang" )*/
    LANG_CODE  ( N_("English"),                                           "en", "eng", "eng" )
    LANG_CODE3 ( N_("Erzya"),                                                   "myv", "myv" )
    LANG_CODE  ( N_("Esperanto"),                                         "eo", "epo", "epo" )
    LANG_CODE  ( N_("Estonian"),                                          "et", "est", "est" )
    LANG_CODE  ( N_("Ewe"),                                               "ee", "ewe", "ewe" )
    LANG_CODE3 ( N_("Ewondo"),                                                  "ewo", "ewo" )
    LANG_CODE3 ( N_("Fang"),                                                    "fan", "fan" )
    LANG_CODE3 ( N_("Fanti"),                                                   "fat", "fat" )
    LANG_CODE  ( N_("Faroese"),                                           "fo", "fao", "fao" )
    LANG_CODE3 ( N_("Fiji Hindi"),                                              "hif", "hif" )
    LANG_CODE  ( N_("Fijian"),                                            "fj", "fij", "fij" )
    LANG_CODE3 ( N_("Filipino; Pilipino"),                                      "fil", "fil" )
    LANG_CODE  ( N_("Finnish"),                                           "fi", "fin", "fin" )
    LANG_CODE3 ( N_("Finno-Ugrian (Other)"),                                    "fiu", "fiu" )
    LANG_CODE3 ( N_("Fon"),                                                     "fon", "fon" )
  /*LANG_CODE3 ( N_("French, Middle (ca.1400-1800)"),                           "frm", "frm" )*/
  /*LANG_CODE3 ( N_("French, Old (842-ca.1400)"),                               "fro", "fro" )*/
    LANG_CODE  ( N_("French"),                                            "fr", "fra", "fre" )
    LANG_CODE3 ( N_("Northern Frisian"),                                        "frr", "frr" )
    LANG_CODE3 ( N_("Eastern Frisian"),                                         "frs", "frs" )
    LANG_CODE  ( N_("Western Frisian"),                                   "fy", "fry", "fry" )
    LANG_CODE3 ( N_("Friulian"),                                                "fur", "fur" )
    LANG_CODE  ( N_("Fulah"),                                             "ff", "ful", "ful" )
    LANG_CODE  ( N_("Gaelic; Scottish Gaelic"),                           "gd", "gla", "gla" )
    LANG_CODE  ( N_("Galician"),                                          "gl", "glg", "glg" )
    LANG_CODE3 ( N_("Gan Chinese"),                                             "gan", "gan" )
    LANG_CODE  ( N_("Ganda"),                                             "lg", "lug", "lug" )
    LANG_CODE3 ( N_("Gayo"),                                                    "gay", "gay" )
    LANG_CODE3 ( N_("Ga"),                                                      "gaa", "gaa" )
    LANG_CODE3 ( N_("Gbaya"),                                                   "gba", "gba" )
    LANG_CODE3 ( N_("Geez"),                                                    "gez", "gez" )
    LANG_CODE  ( N_("Georgian"),                                          "ka", "kat", "geo" )
  /*LANG_CODE3 ( N_("German, Middle High (ca.1050-1500)"),                      "gmh", "gmh" )*/
  /*LANG_CODE3 ( N_("German, Old High (ca.750-1050)"),                          "goh", "goh" )*/
    LANG_CODE3 ( N_("Germanic (Other)"),                                        "gem", "gem" )
    LANG_CODE  ( N_("German"),                                            "de", "deu", "ger" )
    LANG_CODE3 ( N_("Swiss German; Alemannic"),                                 "gsw", "gsw" )
    LANG_CODE3 ( N_("Gilbertese"),                                              "gil", "gil" )
    LANG_CODE3 ( N_("Gondi"),                                                   "gon", "gon" )
    LANG_CODE3 ( N_("Gorontalo"),                                               "gor", "gor" )
    LANG_CODE3 ( N_("Gothic"),                                                  "got", "got" )
    LANG_CODE3 ( N_("Grebo"),                                                   "grb", "grb" )
  /*LANG_CODE3 ( N_("Greek, Ancient (to 1453)"),                                "grc", "grc" )*/
    LANG_CODE  ( N_("Greek, Modern"),                                     "el", "ell", "gre" ) /* note: simplified label */
    LANG_CODE  ( N_("Guarani"),                                           "gn", "grn", "grn" )
    LANG_CODE  ( N_("Gujarati"),                                          "gu", "guj", "guj" )
    LANG_CODE3 ( N_("Gwich´in"),                                                "gwi", "gwi" )
    LANG_CODE3 ( N_("Haida"),                                                   "hai", "hai" )
    LANG_CODE  ( N_("Haitian; Haitian Creole"),                           "ht", "hat", "hat" )
    LANG_CODE3 ( N_("Hakka Chinese"),                                           "hak", "hak" )
    LANG_CODE  ( N_("Hausa"),                                             "ha", "hau", "hau" )
    LANG_CODE3 ( N_("Hawaiian"),                                                "haw", "haw" )
    LANG_CODE  ( N_("Hebrew"),                                            "he", "heb", "heb" )
    LANG_CODE  ( N_("Herero"),                                            "hz", "her", "her" )
    LANG_CODE3 ( N_("Hiligaynon"),                                              "hil", "hil" )
    LANG_CODE3 ( N_("Himachali"),                                               "him", "him" )
    LANG_CODE  ( N_("Hindi"),                                             "hi", "hin", "hin" )
    LANG_CODE  ( N_("Hiri Motu"),                                         "ho", "hmo", "hmo" )
    LANG_CODE3 ( N_("Hittite"),                                                 "hit", "hit" )
    LANG_CODE3 ( N_("Hmong"),                                                   "hmn", "hmn" )
    LANG_CODE3 ( N_("Huizhou Chinese"),                                         "czh", "czh" )
    LANG_CODE  ( N_("Hungarian"),                                         "hu", "hun", "hun" )
    LANG_CODE3 ( N_("Hupa"),                                                    "hup", "hup" )
    LANG_CODE3 ( N_("Iban"),                                                    "iba", "iba" )
    LANG_CODE  ( N_("Icelandic"),                                         "is", "isl", "ice" )
    LANG_CODE  ( N_("Ido"),                                               "io", "ido", "ido" )
    LANG_CODE  ( N_("Igbo"),                                              "ig", "ibo", "ibo" )
    LANG_CODE3 ( N_("Ijo"),                                                     "ijo", "ijo" )
    LANG_CODE3 ( N_("Iloko"),                                                   "ilo", "ilo" )
    LANG_CODE3 ( N_("Inari Sami"),                                              "smn", "smn" )
    LANG_CODE3 ( N_("Indic (Other)"),                                           "inc", "inc" )
    LANG_CODE3 ( N_("Indo-European (Other)"),                                   "ine", "ine" )
    LANG_CODE  ( N_("Indonesian"),                                        "id", "ind", "ind" )
    LANG_CODE3 ( N_("Ingush"),                                                  "inh", "inh" )
    LANG_CODE  ( N_("Interlingua"),                                       "ia", "ina", "ina" ) /* note: simplified label */
    LANG_CODE  ( N_("Interlingue"),                                       "ie", "ile", "ile" )
    LANG_CODE  ( N_("Inuktitut"),                                         "iu", "iku", "iku" )
    LANG_CODE  ( N_("Inupiaq"),                                           "ik", "ipk", "ipk" )
    LANG_CODE3 ( N_("Iranian (Other)"),                                         "ira", "ira" )
  /*LANG_CODE3 ( N_("Irish, Middle (900-1200)"),                                "mga", "mga" )*/
  /*LANG_CODE3 ( N_("Irish, Old (to 900)"),                                     "sga", "sga" )*/
    LANG_CODE  ( N_("Irish"),                                             "ga", "gle", "gle" )
    LANG_CODE3 ( N_("Iroquoian languages"),                                     "iro", "iro" )
    LANG_CODE  ( N_("Italian"),                                           "it", "ita", "ita" )
    LANG_CODE  ( N_("Japanese"),                                          "ja", "jpn", "jpn" )
    LANG_CODE  ( N_("Javanese"),                                          "jv", "jav", "jav" )
    LANG_CODE3 ( N_("Jinyu Chinese"),                                           "cjy", "cjy" )
    LANG_CODE3 ( N_("Judeo-Arabic"),                                            "jrb", "jrb" )
    LANG_CODE3 ( N_("Judeo-Persian"),                                           "jpr", "jpr" )
    LANG_CODE3 ( N_("Kabardian"),                                               "kbd", "kbd" )
    LANG_CODE3 ( N_("Kabyle"),                                                  "kab", "kab" )
    LANG_CODE3 ( N_("Kachin"),                                                  "kac", "kac" )
    LANG_CODE  ( N_("Kalaallisut; Greenlandic"),                          "kl", "kal", "kal" )
    LANG_CODE3 ( N_("Kalmyk"),                                                  "xal", "xal" )
    LANG_CODE3 ( N_("Kamba"),                                                   "kam", "kam" )
    LANG_CODE  ( N_("Kannada"),                                           "kn", "kan", "kan" )
    LANG_CODE  ( N_("Kanuri"),                                            "kr", "kau", "kau" )
    LANG_CODE3 ( N_("Kara-Kalpak"),                                             "kaa", "kaa" )
    LANG_CODE3 ( N_("Karachay-Balkar"),                                         "krc", "krc" )
    LANG_CODE3 ( N_("Karbi"),                                                   "mjw", "mjw" )
    LANG_CODE3 ( N_("Karelian"),                                                "krl", "krl" )
    LANG_CODE3 ( N_("Karen"),                                                   "kar", "kar" )
    LANG_CODE  ( N_("Kashmiri"),                                          "ks", "kas", "kas" )
    LANG_CODE3 ( N_("Kashubian"),                                               "csb", "csb" )
    LANG_CODE3 ( N_("Kawi"),                                                    "kaw", "kaw" )
    LANG_CODE  ( N_("Kazakh"),                                            "kk", "kaz", "kaz" )
    LANG_CODE3 ( N_("Khasi"),                                                   "kha", "kha" )
    LANG_CODE  ( N_("Khmer"),                                             "km", "khm", "khm" )
    LANG_CODE3 ( N_("Khoisan (Other)"),                                         "khi", "khi" )
    LANG_CODE3 ( N_("Khotanese"),                                               "kho", "kho" )
    LANG_CODE  ( N_("Kikuyu; Gikuyu"),                                    "ki", "kik", "kik" )
    LANG_CODE3 ( N_("Kimbundu"),                                                "kmb", "kmb" )
    LANG_CODE  ( N_("Kinyarwanda"),                                       "rw", "kin", "kin" )
    LANG_CODE  ( N_("Kirghiz"),                                           "ky", "kir", "kir" )
    LANG_CODE3 ( N_("Klingon; tlhIngan-Hol"),                                   "tlh", "tlh" )
    LANG_CODE  ( N_("Komi"),                                              "kv", "kom", "kom" )
    LANG_CODE  ( N_("Kongo"),                                             "kg", "kon", "kon" )
    LANG_CODE3 ( N_("Konkani"),                                                 "kok", "kok" )
    LANG_CODE  ( N_("Korean"),                                            "ko", "kor", "kor" )
    LANG_CODE3 ( N_("Kosraean"),                                                "kos", "kos" )
    LANG_CODE3 ( N_("Kpelle"),                                                  "kpe", "kpe" )
    LANG_CODE3 ( N_("Kru"),                                                     "kro", "kro" )
    LANG_CODE  ( N_("Kuanyama; Kwanyama"),                                "kj", "kua", "kua" )
    LANG_CODE3 ( N_("Kumyk"),                                                   "kum", "kum" )
    LANG_CODE  ( N_("Kurdish"),                                           "ku", "kur", "kur" )
    LANG_CODE3 ( N_("Kurukh"),                                                  "kru", "kru" )
    LANG_CODE3 ( N_("Kutenai"),                                                 "kut", "kut" )
    LANG_CODE3 ( N_("Ladino"),                                                  "lad", "lad" )
    LANG_CODE3 ( N_("Lahnda"),                                                  "lah", "lah" )
    LANG_CODE3 ( N_("Lamba"),                                                   "lam", "lam" )
    LANG_CODE  ( N_("Lao"),                                               "lo", "lao", "lao" )
    LANG_CODE  ( N_("Latin"),                                             "la", "lat", "lat" )
    LANG_CODE  ( N_("Latvian"),                                           "lv", "lav", "lav" )
    LANG_CODE3 ( N_("Lezghian"),                                                "lez", "lez" )
    LANG_CODE3 ( N_("Ligurian"),                                                "lij", "lij" )
    LANG_CODE  ( N_("Limburgan; Limburger; Limburgish"),                  "li", "lim", "lim" )
    LANG_CODE  ( N_("Lingala"),                                           "ln", "lin", "lin" )
    LANG_CODE3 ( N_("Literary Chinese"),                                        "lzh", "lzh" )
    LANG_CODE  ( N_("Lithuanian"),                                        "lt", "lit", "lit" )
    LANG_CODE3 ( N_("Lojban"),                                                  "jbo", "jbo" )
    LANG_CODE3 ( N_("Low German; Low Saxon"),                                   "nds", "nds" ) /* note: simplified label */
    LANG_CODE3 ( N_("Lower Sorbian"),                                           "dsb", "dsb" )
    LANG_CODE3 ( N_("Lozi"),                                                    "loz", "loz" )
    LANG_CODE  ( N_("Luba-Katanga"),                                      "lu", "lub", "lub" )
    LANG_CODE3 ( N_("Luba-Lulua"),                                              "lua", "lua" )
    LANG_CODE3 ( N_("Luiseno"),                                                 "lui", "lui" )
    LANG_CODE3 ( N_("Lule Sami"),                                               "smj", "smj" )
    LANG_CODE3 ( N_("Lunda"),                                                   "lun", "lun" )
    LANG_CODE3 ( N_("Luo (Kenya and Tanzania)"),                                "luo", "luo" )
    LANG_CODE3 ( N_("Lushai"),                                                  "lus", "lus" )
    LANG_CODE  ( N_("Luxembourgish; Letzeburgesch"),                      "lb", "ltz", "ltz" )
    LANG_CODE  ( N_("Macedonian"),                                        "mk", "mkd", "mac" )
    LANG_CODE3 ( N_("Madurese"),                                                "mad", "mad" )
    LANG_CODE3 ( N_("Magahi"),                                                  "mag", "mag" )
    LANG_CODE3 ( N_("Maithili"),                                                "mai", "mai" )
    LANG_CODE3 ( N_("Makasar"),                                                 "mak", "mak" )
    LANG_CODE  ( N_("Malagasy"),                                          "mg", "mlg", "mlg" )
    LANG_CODE  ( N_("Malayalam"),                                         "ml", "mal", "mal" )
    LANG_CODE  ( N_("Malay"),                                             "ms", "msa", "may" )
    LANG_CODE  ( N_("Maltese"),                                           "mt", "mlt", "mlt" )
    LANG_CODE3 ( N_("Manchu"),                                                  "mnc", "mnc" )
    LANG_CODE3 ( N_("Mandarin Chinese"),                                        "cmn", "cmn" )
    LANG_CODE3 ( N_("Mandar"),                                                  "mdr", "mdr" )
    LANG_CODE3 ( N_("Mandingo"),                                                "man", "man" )
    LANG_CODE3 ( N_("Manipuri"),                                                "mni", "mni" )
    LANG_CODE3 ( N_("Manobo languages"),                                        "mno", "mno" )
    LANG_CODE  ( N_("Manx"),                                              "gv", "glv", "glv" )
    LANG_CODE  ( N_("Maori"),                                             "mi", "mri", "mao" )
    LANG_CODE  ( N_("Marathi"),                                           "mr", "mar", "mar" )
    LANG_CODE3 ( N_("Mari"),                                                    "chm", "chm" )
    LANG_CODE  ( N_("Marshallese"),                                       "mh", "mah", "mah" )
    LANG_CODE3 ( N_("Marwari"),                                                 "mwr", "mwr" )
    LANG_CODE3 ( N_("Masai"),                                                   "mas", "mas" )
    LANG_CODE3 ( N_("Morisyen"),                                                "mfe", "mfe" )
    LANG_CODE3 ( N_("Mayan languages"),                                         "myn", "myn" )
    LANG_CODE3 ( N_("Meadow Mari"),                                             "mhr", "mhr" )
    LANG_CODE3 ( N_("Mende"),                                                   "men", "men" )
    LANG_CODE3 ( N_("Mi'kmaq; Micmac"),                                         "mic", "mic" )
    LANG_CODE3 ( N_("Miskito"),                                                 "miq", "miq" )
    LANG_CODE3 ( N_("Minangkabau"),                                             "min", "min" )
    LANG_CODE3 ( N_("Min Bei Chinese"),                                         "mnp", "mnp" )
    LANG_CODE3 ( N_("Min Dong Chinese"),                                        "cdo", "cdo" )
    LANG_CODE3 ( N_("Min Nan Chinese"),                                         "nan", "nan" )
    LANG_CODE3 ( N_("Min Zhong Chinese"),                                       "czo", "czo" )
    LANG_CODE3 ( N_("Mirandese"),                                               "mwl", "mwl" )
    LANG_CODE3 ( N_("Miscellaneous languages"),                                 "mis", "mis" )
    LANG_CODE3 ( N_("Mohawk"),                                                  "moh", "moh" )
    LANG_CODE3 ( N_("Moksha"),                                                  "mdf", "mdf" )
    LANG_CODE  ( N_("Moldavian"),                                         "mo", "mol", "mol" )
    LANG_CODE3 ( N_("Mon"),                                                     "mnw", "mnw" )
    LANG_CODE3 ( N_("Mon-Khmer (Other)"),                                       "mkh", "mkh" )
    LANG_CODE  ( N_("Mongolian"),                                         "mn", "mon", "mon" )
    LANG_CODE3 ( N_("Mongo"),                                                   "lol", "lol" )
    LANG_CODE3 ( N_("Moroccan Arabic"),                                         "ary", "ary" )
    LANG_CODE3 ( N_("Mossi"),                                                   "mos", "mos" )
    LANG_CODE3 ( N_("Multiple languages"),                                      "mul", "mul" )
    LANG_CODE3 ( N_("Munda languages"),                                         "mun", "mun" )
    LANG_CODE3 ( N_("Nahuatl"),                                                 "nah", "nah" )
    LANG_CODE  ( N_("Nauru"),                                             "na", "nau", "nau" )
    LANG_CODE  ( N_("Navajo; Navaho"),                                    "nv", "nav", "nav" )
    LANG_CODE  ( N_("Ndebele, North; North Ndebele"),                     "nd", "nde", "nde" )
    LANG_CODE  ( N_("Ndebele, South; South Ndebele"),                     "nr", "nbl", "nbl" )
    LANG_CODE  ( N_("Ndonga"),                                            "ng", "ndo", "ndo" )
    LANG_CODE3 ( N_("Neapolitan"),                                              "nap", "nap" )
    LANG_CODE3 ( N_("Nepal Bhasa; Newari"),                                     "new", "new" )
    LANG_CODE  ( N_("Nepali"),                                            "ne", "nep", "nep" )
    LANG_CODE3 ( N_("Nias"),                                                    "nia", "nia" )
    LANG_CODE3 ( N_("Niger-Kordofanian (Other)"),                               "nic", "nic" )
    LANG_CODE3 ( N_("Nilo-Saharan (Other)"),                                    "ssa", "ssa" )
    LANG_CODE3 ( N_("Niuean"),                                                  "niu", "niu" )
    LANG_CODE3 ( N_("N'Ko"),                                                    "nqo", "nqo" )
    LANG_CODE3 ( N_("Nogai"),                                                   "nog", "nog" )
  /*LANG_CODE3 ( N_("Norse, Old"),                                              "non", "non" )*/
    LANG_CODE3 ( N_("North American Indian"),                                   "nai", "nai" )
    LANG_CODE  ( N_("Northern Sami"),                                     "se", "sme", "sme" )
    LANG_CODE3 ( N_("Northern Sotho; Pedi; Sepedi"),                            "nso", "nso" )
    LANG_CODE  ( N_("Norwegian Bokmål"),                                  "nb", "nob", "nob" )
    LANG_CODE  ( N_("Norwegian Nynorsk"),                                 "nn", "nno", "nno" )
    LANG_CODE  ( N_("Norwegian"),                                         "no", "nor", "nor" )
    LANG_CODE3 ( N_("Nubian languages"),                                        "nub", "nub" )
    LANG_CODE3 ( N_("Nyamwezi"),                                                "nym", "nym" )
    LANG_CODE3 ( N_("Nyankole"),                                                "nyn", "nyn" )
    LANG_CODE3 ( N_("Nyoro"),                                                   "nyo", "nyo" )
    LANG_CODE3 ( N_("Nzima"),                                                   "nzi", "nzi" )
    LANG_CODE  ( N_("Occitan; Provençal"),                                "oc", "oci", "oci" ) /* note: simplified label */
    LANG_CODE  ( N_("Ojibwa"),                                            "oj", "oji", "oji" )
    LANG_CODE  ( N_("Odia"),                                              "or", "ori", "ori" )
    LANG_CODE  ( N_("Oromo"),                                             "om", "orm", "orm" )
    LANG_CODE3 ( N_("Osage"),                                                   "osa", "osa" )
    LANG_CODE  ( N_("Ossetian; Ossetic"),                                 "os", "oss", "oss" )
    LANG_CODE3 ( N_("Otomian languages"),                                       "oto", "oto" )
    LANG_CODE3 ( N_("Pahlavi"),                                                 "pal", "pal" )
    LANG_CODE3 ( N_("Palauan"),                                                 "pau", "pau" )
    LANG_CODE  ( N_("Pali"),                                              "pi", "pli", "pli" )
    LANG_CODE3 ( N_("Pampanga"),                                                "pam", "pam" )
    LANG_CODE3 ( N_("Pangasinan"),                                              "pag", "pag" )
    LANG_CODE  ( N_("Panjabi; Punjabi"),                                  "pa", "pan", "pan" )
    LANG_CODE3 ( N_("Papiamento"),                                              "pap", "pap" )
    LANG_CODE3 ( N_("Papuan (Other)"),                                          "paa", "paa" )
  /*LANG_CODE3 ( N_("Persian, Old (ca.600-400 B.C.)"),                          "peo", "peo" )*/
    LANG_CODE  ( N_("Persian"),                                           "fa", "fas", "per" )
    LANG_CODE3 ( N_("Philippine (Other)"),                                      "phi", "phi" )
    LANG_CODE3 ( N_("Phoenician"),                                              "phn", "phn" )
    LANG_CODE3 ( N_("Pohnpeian"),                                               "pon", "pon" )
    LANG_CODE  ( N_("Polish"),                                            "pl", "pol", "pol" )
    LANG_CODE  ( N_("Portuguese"),                                        "pt", "por", "por" )
    LANG_CODE3 ( N_("Prakrit languages"),                                       "pra", "pra" )
  /*LANG_CODE3 ( N_("Provençal, Old (to 1500)"),                                "pro", "pro" )*/
    LANG_CODE3 ( N_("Pu-Xian Chinese"),                                         "cpx", "cpx" )
    LANG_CODE  ( N_("Pushto"),                                            "ps", "pus", "pus" )
    LANG_CODE  ( N_("Quechua"),                                           "qu", "que", "que" )
    LANG_CODE3 ( N_("Quechua, Southern"),                                       "quz", "quz" )
    LANG_CODE  ( N_("Raeto-Romance"),                                     "rm", "roh", "roh" )
    LANG_CODE3 ( N_("Rajasthani"),                                              "raj", "raj" )
    LANG_CODE3 ( N_("Rapanui"),                                                 "rap", "rap" )
    LANG_CODE3 ( N_("Rarotongan"),                                              "rar", "rar" )
    LANG_CODE3 ( N_("Romance (Other)"),                                         "roa", "roa" )
    LANG_CODE  ( N_("Romanian"),                                          "ro", "ron", "rum" )
    LANG_CODE3 ( N_("Romany"),                                                  "rom", "rom" )
    LANG_CODE  ( N_("Rundi"),                                             "rn", "run", "run" )
    LANG_CODE  ( N_("Russian"),                                           "ru", "rus", "rus" )
    LANG_CODE3 ( N_("Samogitian"),                                              "sgs", "sgs" )
    LANG_CODE3 ( N_("Salishan languages"),                                      "sal", "sal" )
    LANG_CODE3 ( N_("Samaritan Aramaic"),                                       "sam", "sam" )
    LANG_CODE3 ( N_("Sami languages (Other)"),                                  "smi", "smi" )
    LANG_CODE  ( N_("Samoan"),                                            "sm", "smo", "smo" )
    LANG_CODE3 ( N_("Sandawe"),                                                 "sad", "sad" )
    LANG_CODE  ( N_("Sango"),                                             "sg", "sag", "sag" )
    LANG_CODE  ( N_("Sanskrit"),                                          "sa", "san", "san" )
    LANG_CODE3 ( N_("Santali"),                                                 "sat", "sat" )
    LANG_CODE  ( N_("Sardinian"),                                         "sc", "srd", "srd" )
    LANG_CODE3 ( N_("Sasak"),                                                   "sas", "sas" )
    LANG_CODE3 ( N_("Scots"),                                                   "sco", "sco" )
    LANG_CODE3 ( N_("Selkup"),                                                  "sel", "sel" )
    LANG_CODE3 ( N_("Semitic (Other)"),                                         "sem", "sem" )
    LANG_CODE  ( N_("Serbian"),                                           "sr", "srp", "scc" )
    LANG_CODE3 ( N_("Serer"),                                                   "srr", "srr" )
    LANG_CODE3 ( N_("Shan"),                                                    "shn", "shn" )
    LANG_CODE  ( N_("Shona"),                                             "sn", "sna", "sna" )
    LANG_CODE3 ( N_("Shuswap"),                                                 "shs", "shs" )
    LANG_CODE  ( N_("Sichuan Yi"),                                        "ii", "iii", "iii" )
    LANG_CODE3 ( N_("Sicilian"),                                                "scn", "scn" )
    LANG_CODE3 ( N_("Sidamo"),                                                  "sid", "sid" )
    LANG_CODE3 ( N_("Sign Languages"),                                          "sgn", "sgn" )
    LANG_CODE3 ( N_("Siksika"),                                                 "bla", "bla" )
    LANG_CODE3 ( N_("Silesian"),                                                "szl", "szl" )
    LANG_CODE  ( N_("Sindhi"),                                            "sd", "snd", "snd" )
    LANG_CODE  ( N_("Sinhala; Sinhalese"),                                "si", "sin", "sin" )
    LANG_CODE3 ( N_("Sino-Tibetan (Other)"),                                    "sit", "sit" )
    LANG_CODE3 ( N_("Siouan languages"),                                        "sio", "sio" )
    LANG_CODE3 ( N_("Skolt Sami"),                                              "sms", "sms" )
    LANG_CODE3 ( N_("Slave (Athapascan)"),                                      "den", "den" )
    LANG_CODE3 ( N_("Slavic (Other)"),                                          "sla", "sla" )
    LANG_CODE  ( N_("Slovak"),                                            "sk", "slk", "slo" )
    LANG_CODE  ( N_("Slovenian"),                                         "sl", "slv", "slv" )
    LANG_CODE3 ( N_("Sogdian"),                                                 "sog", "sog" )
    LANG_CODE  ( N_("Somali"),                                            "so", "som", "som" )
    LANG_CODE3 ( N_("Songhai"),                                                 "son", "son" )
    LANG_CODE3 ( N_("Soninke"),                                                 "snk", "snk" )
    LANG_CODE3 ( N_("Sorani"),                                                  "ckb", "ckb" )
    LANG_CODE3 ( N_("Sorbian languages"),                                       "wen", "wen" )
    LANG_CODE  ( N_("Sotho, Southern"),                                   "st", "sot", "sot" )
    LANG_CODE3 ( N_("South American Indian (Other)"),                           "sai", "sai" )
    LANG_CODE3 ( N_("Southern Sami"),                                           "sma", "sma" )
    LANG_CODE  ( N_("Spanish; Castilian"),                                "es", "spa", "spa" )
    LANG_CODE3 ( N_("Sranan Tongo"),                                            "srn", "srn" )
    LANG_CODE3 ( N_("Sukuma"),                                                  "suk", "suk" )
    LANG_CODE3 ( N_("Sumerian"),                                                "sux", "sux" )
    LANG_CODE  ( N_("Sundanese"),                                         "su", "sun", "sun" )
    LANG_CODE3 ( N_("Susu"),                                                    "sus", "sus" )
    LANG_CODE  ( N_("Swahili"),                                           "sw", "swa", "swa" )
    LANG_CODE  ( N_("Swati"),                                             "ss", "ssw", "ssw" )
    LANG_CODE  ( N_("Swedish"),                                           "sv", "swe", "swe" )
  /*LANG_CODE3 ( N_("Classical Syriac"),                                        "syc", "syc" )*/
    LANG_CODE3 ( N_("Syriac"),                                                  "syr", "syr" )
    LANG_CODE  ( N_("Tagalog"),                                           "tl", "tgl", "tgl" )
    LANG_CODE  ( N_("Tahitian"),                                          "ty", "tah", "tah" )
    LANG_CODE3 ( N_("Tai (Other)"),                                             "tai", "tai" )
    LANG_CODE  ( N_("Tajik"),                                             "tg", "tgk", "tgk" )
    LANG_CODE3 ( N_("Talossan"),                                                "tzl", "tzl" )
    LANG_CODE3 ( N_("Tamashek"),                                                "tmh", "tmh" )
    LANG_CODE  ( N_("Tamil"),                                             "ta", "tam", "tam" )
    LANG_CODE  ( N_("Tatar"),                                             "tt", "tat", "tat" )
    LANG_CODE  ( N_("Telugu"),                                            "te", "tel", "tel" )
    LANG_CODE3 ( N_("Tereno"),                                                  "ter", "ter" )
    LANG_CODE3 ( N_("Tetum"),                                                   "tet", "tet" )
    LANG_CODE  ( N_("Thai"),                                              "th", "tha", "tha" )
    LANG_CODE3 ( N_("Tharu, Chitwani"),                                         "the", "the" )
    LANG_CODE  ( N_("Tibetan"),                                           "bo", "bod", "tib" )
    LANG_CODE3 ( N_("Tigre"),                                                   "tig", "tig" )
    LANG_CODE  ( N_("Tigrinya"),                                          "ti", "tir", "tir" )
    LANG_CODE3 ( N_("Timne"),                                                   "tem", "tem" )
    LANG_CODE3 ( N_("Tiv"),                                                     "tiv", "tiv" )
    LANG_CODE3 ( N_("Tlingit"),                                                 "tli", "tli" )
    LANG_CODE3 ( N_("Tok Pisin"),                                               "tpi", "tpi" )
    LANG_CODE3 ( N_("Tokelau"),                                                 "tkl", "tkl" )
    LANG_CODE3 ( N_("Tonga (Nyasa)"),                                           "tog", "tog" )
    LANG_CODE  ( N_("Tonga (Tonga Islands)"),                             "to", "ton", "ton" )
    LANG_CODE3 ( N_("Tsimshian"),                                               "tsi", "tsi" )
    LANG_CODE  ( N_("Tsonga"),                                            "ts", "tso", "tso" )
    LANG_CODE  ( N_("Tswana"),                                            "tn", "tsn", "tsn" )
    LANG_CODE3 ( N_("Tulu"),                                                    "tcy", "tcy" )
    LANG_CODE3 ( N_("Tumbuka"),                                                 "tum", "tum" )
    LANG_CODE3 ( N_("Tupi languages"),                                          "tup", "tup" )
  /*LANG_CODE3 ( N_("Turkish, Ottoman (1500-1928)"),                            "ota", "ota" )*/
    LANG_CODE  ( N_("Turkish"),                                           "tr", "tur", "tur" )
    LANG_CODE  ( N_("Turkmen"),                                           "tk", "tuk", "tuk" )
    LANG_CODE3 ( N_("Tuvalu"),                                                  "tvl", "tvl" )
    LANG_CODE3 ( N_("Tuvinian"),                                                "tyv", "tyv" )
    LANG_CODE  ( N_("Twi"),                                               "tw", "twi", "twi" )
    LANG_CODE3 ( N_("Udmurt"),                                                  "udm", "udm" )
    LANG_CODE3 ( N_("Ugaritic"),                                                "uga", "uga" )
    LANG_CODE  ( N_("Uighur; Uyghur"),                                    "ug", "uig", "uig" )
    LANG_CODE  ( N_("Ukrainian"),                                         "uk", "ukr", "ukr" )
    LANG_CODE3 ( N_("Umbundu"),                                                 "umb", "umb" )
    LANG_CODE3 ( N_("Unami Delaware"),                                          "unm", "unm" )
    LANG_CODE3 ( N_("Undetermined"),                                            "und", "und" )
    LANG_CODE3 ( N_("Upper Sorbian"),                                           "hsb", "hsb" )
    LANG_CODE  ( N_("Urdu"),                                              "ur", "urd", "urd" )
    LANG_CODE  ( N_("Uzbek"),                                             "uz", "uzb", "uzb" )
    LANG_CODE3 ( N_("Vai"),                                                     "vai", "vai" )
    LANG_CODE  ( N_("Venda"),                                             "ve", "ven", "ven" )
    LANG_CODE  ( N_("Vietnamese"),                                        "vi", "vie", "vie" )
    LANG_CODE  ( N_("Volapük"),                                           "vo", "vol", "vol" )
    LANG_CODE3 ( N_("Votic"),                                                   "vot", "vot" )
    LANG_CODE3 ( N_("Wakashan languages"),                                      "wak", "wak" )
    LANG_CODE3 ( N_("Walser"),                                                  "wae", "wae" )
    LANG_CODE3 ( N_("Walaita"),                                                 "wal", "wal" )
    LANG_CODE  ( N_("Walloon"),                                           "wa", "wln", "wln" )
    LANG_CODE3 ( N_("Waray"),                                                   "war", "war" )
    LANG_CODE3 ( N_("Washo"),                                                   "was", "was" )
    LANG_CODE  ( N_("Welsh"),                                             "cy", "cym", "wel" )
    LANG_CODE  ( N_("Wolof"),                                             "wo", "wol", "wol" )
    LANG_CODE3 ( N_("Wu Chinese"),                                              "wuu", "wuu" )
    LANG_CODE  ( N_("Xhosa"),                                             "xh", "xho", "xho" )
    LANG_CODE3 ( N_("Xiang Chinese"),                                           "hsn", "hsn" )
    LANG_CODE3 ( N_("Yakut"),                                                   "sah", "sah" )
    LANG_CODE3 ( N_("Yao"),                                                     "yao", "yao" )
    LANG_CODE3 ( N_("Yau (Uruwa)"),                                             "yuw", "yuw" )
    LANG_CODE3 ( N_("Yapese"),                                                  "yap", "yap" )
    LANG_CODE  ( N_("Yiddish"),                                           "yi", "yid", "yid" )
    LANG_CODE  ( N_("Yoruba"),                                            "yo", "yor", "yor" )
    LANG_CODE3 ( N_("Yue Chinese"),                                             "yue", "yue" )
    LANG_CODE3 ( N_("Yupik languages"),                                         "ypk", "ypk" )
    LANG_CODE3 ( N_("Zande"),                                                   "znd", "znd" )
    LANG_CODE3 ( N_("Zapotec"),                                                 "zap", "zap" )
    LANG_CODE3 ( N_("Zenaga"),                                                  "zen", "zen" )
    LANG_CODE  ( N_("Zhuang; Chuang"),                                    "za", "zha", "zha" )
    LANG_CODE  ( N_("Zulu"),                                              "zu", "zul", "zul" )
    LANG_CODE3 ( N_("Zuni"),                                                    "zun", "zun" )
    LANG_CODE3 ( N_("Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki"),          "zza", "zza" )
=======
    { N_( "Afar" ),                           "aa", "aar", "aar" },
    { N_( "Abkhazian" ),                      "ab", "abk", "abk" },
    { N_( "Afrikaans" ),                      "af", "afr", "afr" },
    { N_( "Albanian" ),                       "sq", "sqi", "alb" },
    { N_( "Amharic" ),                        "am", "amh", "amh" },
    { N_( "Arabic" ),                         "ar", "ara", "ara" },
    { N_( "Armenian" ),                       "hy", "hye", "arm" },
    { N_( "Assamese" ),                       "as", "asm", "asm" },
    { N_( "Avestan" ),                        "ae", "ave", "ave" },
    { N_( "Aymara" ),                         "ay", "aym", "aym" },
    { N_( "Azerbaijani" ),                    "az", "aze", "aze" },
    { N_( "Bashkir" ),                        "ba", "bak", "bak" },
    { N_( "Basque" ),                         "eu", "eus", "baq" },
    { N_( "Belarusian" ),                     "be", "bel", "bel" },
    { N_( "Bengali" ),                        "bn", "ben", "ben" },
    { N_( "Bihari" ),                         "bh", "bih", "bih" },
    { N_( "Bislama" ),                        "bi", "bis", "bis" },
    { N_( "Bosnian" ),                        "bs", "bos", "bos" },
    { N_( "Breton" ),                         "br", "bre", "bre" },
    { N_( "Bulgarian" ),                      "bg", "bul", "bul" },
    { N_( "Burmese" ),                        "my", "mya", "bur" },
    { N_( "Catalan" ),                        "ca", "cat", "cat" },
    { N_( "Chamorro" ),                       "ch", "cha", "cha" },
    { N_( "Chechen" ),                        "ce", "che", "che" },
    { N_( "Chinese" ),                        "zh", "zho", "chi" },
    { N_( "Church Slavic" ),                  "cu", "chu", "chu" },
    { N_( "Chuvash" ),                        "cv", "chv", "chv" },
    { N_( "Cornish" ),                        "kw", "cor", "cor" },
    { N_( "Corsican" ),                       "co", "cos", "cos" },
    { N_( "Czech" ),                          "cs", "ces", "cze" },
    { N_( "Danish" ),                         "da", "dan", "dan" },
    { N_( "Dutch" ),                          "nl", "nld", "dut" },
    { N_( "Dzongkha" ),                       "dz", "dzo", "dzo" },
    { N_( "English" ),                        "en", "eng", "eng" },
    { N_( "Esperanto" ),                      "eo", "epo", "epo" },
    { N_( "Estonian" ),                       "et", "est", "est" },
    { N_( "Faroese" ),                        "fo", "fao", "fao" },
    { N_( "Fijian" ),                         "fj", "fij", "fij" },
    { N_( "Finnish" ),                        "fi", "fin", "fin" },
    { N_( "French" ),                         "fr", "fra", "fre" },
    { N_( "Frisian" ),                        "fy", "fry", "fry" },
    { N_( "Georgian" ),                       "ka", "kat", "geo" },
    { N_( "German" ),                         "de", "deu", "ger" },
    { N_( "Gaelic (Scots)" ),                 "gd", "gla", "gla" },
    { N_( "Irish" ),                          "ga", "gle", "gle" },
    { N_( "Gallegan" ),                       "gl", "glg", "glg" },
    { N_( "Manx" ),                           "gv", "glv", "glv" },
    { N_( "Greek, Modern" ),                  "el", "gre", "ell" },
    { N_( "Guarani" ),                        "gn", "grn", "grn" },
    { N_( "Gujarati" ),                       "gu", "guj", "guj" },
    { N_( "Hebrew" ),                         "he", "heb", "heb" },
    { N_( "Herero" ),                         "hz", "her", "her" },
    { N_( "Hindi" ),                          "hi", "hin", "hin" },
    { N_( "Hiri Motu" ),                      "ho", "hmo", "hmo" },
    { N_( "Hungarian" ),                      "hu", "hun", "hun" },
    { N_( "Icelandic" ),                      "is", "isl", "ice" },
    { N_( "Inuktitut" ),                      "iu", "iku", "iku" },
    { N_( "Interlingue" ),                    "ie", "ile", "ile" },
    { N_( "Interlingua" ),                    "ia", "ina", "ina" },
    { N_( "Indonesian" ),                     "id", "ind", "ind" },
    { N_( "Inupiaq" ),                        "ik", "ipk", "ipk" },
    { N_( "Italian" ),                        "it", "ita", "ita" },
    { N_( "Hebrew" ),                         "iw", "heb", "heb" },
    { N_( "Javanese" ),                       "jv", "jaw", "jav" },
    { N_( "Japanese" ),                       "ja", "jpn", "jpn" },
    { N_( "Greenlandic, Kalaallisut" ),       "kl", "kal", "kal" },
    { N_( "Kannada" ),                        "kn", "kan", "kan" },
    { N_( "Kashmiri" ),                       "ks", "kas", "kas" },
    { N_( "Kazakh" ),                         "kk", "kaz", "kaz" },
    { N_( "Khmer" ),                          "km", "khm", "khm" },
    { N_( "Kikuyu" ),                         "ki", "kik", "kik" },
    { N_( "Kinyarwanda" ),                    "rw", "kin", "kin" },
    { N_( "Kirghiz" ),                        "ky", "kir", "kir" },
    { N_( "Komi" ),                           "kv", "kom", "kom" },
    { N_( "Korean" ),                         "ko", "kor", "kor" },
    { N_( "Kuanyama" ),                       "kj", "kua", "kua" },
    { N_( "Kurdish" ),                        "ku", "kur", "kur" },
    { N_( "Lao" ),                            "lo", "lao", "lao" },
    { N_( "Latin" ),                          "la", "lat", "lat" },
    { N_( "Latvian" ),                        "lv", "lav", "lav" },
    { N_( "Lingala" ),                        "ln", "lin", "lin" },
    { N_( "Lithuanian" ),                     "lt", "lit", "lit" },
    { N_( "Letzeburgesch" ),                  "lb", "ltz", "ltz" },
    { N_( "Macedonian" ),                     "mk", "mkd", "mac" },
    { N_( "Marshall" ),                       "mh", "mah", "mah" },
    { N_( "Malayalam" ),                      "ml", "mal", "mal" },
    { N_( "Maori" ),                          "mi", "mri", "mao" },
    { N_( "Marathi" ),                        "mr", "mar", "mar" },
    { N_( "Malay" ),                          "ms", "msa", "may" },
    { N_( "Malagasy" ),                       "mg", "mlg", "mlg" },
    { N_( "Maltese" ),                        "mt", "mlt", "mlt" },
    { N_( "Moldavian" ),                      "mo", "mol", "mol" },
    { N_( "Mongolian" ),                      "mn", "mon", "mon" },
    { N_( "Nauru" ),                          "na", "nau", "nau" },
    { N_( "Navajo" ),                         "nv", "nav", "nav" },
    { N_( "Ndebele, South" ),                 "nr", "nbl", "nbl" },
    { N_( "Ndebele, North" ),                 "nd", "nde", "nde" },
    { N_( "Ndonga" ),                         "ng", "ndo", "ndo" },
    { N_( "Nepali" ),                         "ne", "nep", "nep" },
    { N_( "Norwegian" ),                      "no", "nor", "nor" },
    { N_( "Norwegian Nynorsk" ),              "nn", "nno", "nno" },
    { N_( "Norwegian Bokmaal" ),              "nb", "nob", "nob" },
    { N_( "Chichewa; Nyanja" ),               "ny", "nya", "nya" },
    { N_( "Occitan; Provençal" ),             "oc", "oci", "oci" },
    { N_( "Oriya" ),                          "or", "ori", "ori" },
    { N_( "Oromo" ),                          "om", "orm", "orm" },
    { N_( "On Screen Display" ),              "od", "osd", "osd" },
    { N_( "Ossetian; Ossetic" ),              "os", "oss", "oss" },
    { N_( "Panjabi" ),                        "pa", "pan", "pan" },
    { N_( "Persian" ),                        "fa", "fas", "per" },
    { N_( "Pali" ),                           "pi", "pli", "pli" },
    { N_( "Polish" ),                         "pl", "pol", "pol" },
    { N_( "Portuguese" ),                     "pt", "por", "por" },
    { N_( "Pushto" ),                         "ps", "pus", "pus" },
    { N_( "Quechua" ),                        "qu", "que", "que" },
    { N_( "Original audio" ),                 "",   "qaa", "qaa" },
    { N_( "Raeto-Romance" ),                  "rm", "roh", "roh" },
    { N_( "Romanian" ),                       "ro", "ron", "rum" },
    { N_( "Rundi" ),                          "rn", "run", "run" },
    { N_( "Russian" ),                        "ru", "rus", "rus" },
    { N_( "Sango" ),                          "sg", "sag", "sag" },
    { N_( "Sanskrit" ),                       "sa", "san", "san" },
    { N_( "Serbian" ),                        "sr", "srp", "scc" },
    { N_( "Croatian" ),                       "hr", "hrv", "scr" },
    { N_( "Sinhalese" ),                      "si", "sin", "sin" },
    { N_( "Slovak" ),                         "sk", "slk", "slo" },
    { N_( "Slovenian" ),                      "sl", "slv", "slv" },
    { N_( "Northern Sami" ),                  "se", "sme", "sme" },
    { N_( "Samoan" ),                         "sm", "smo", "smo" },
    { N_( "Shona" ),                          "sn", "sna", "sna" },
    { N_( "Sindhi" ),                         "sd", "snd", "snd" },
    { N_( "Somali" ),                         "so", "som", "som" },
    { N_( "Sotho, Southern" ),                "st", "sot", "sot" },
    { N_( "Spanish" ),                        "es", "spa", "spa" },
    { N_( "Sardinian" ),                      "sc", "srd", "srd" },
    { N_( "Swati" ),                          "ss", "ssw", "ssw" },
    { N_( "Sundanese" ),                      "su", "sun", "sun" },
    { N_( "Swahili" ),                        "sw", "swa", "swa" },
    { N_( "Swedish" ),                        "sv", "swe", "swe" },
    { N_( "Tahitian" ),                       "ty", "tah", "tah" },
    { N_( "Tamil" ),                          "ta", "tam", "tam" },
    { N_( "Tatar" ),                          "tt", "tat", "tat" },
    { N_( "Telugu" ),                         "te", "tel", "tel" },
    { N_( "Tajik" ),                          "tg", "tgk", "tgk" },
    { N_( "Tagalog" ),                        "tl", "tgl", "tgl" },
    { N_( "Thai" ),                           "th", "tha", "tha" },
    { N_( "Tibetan" ),                        "bo", "bod", "tib" },
    { N_( "Tigrinya" ),                       "ti", "tir", "tir" },
    { N_( "Tonga (Tonga Islands)" ),          "to", "ton", "ton" },
    { N_( "Tswana" ),                         "tn", "tsn", "tsn" },
    { N_( "Tsonga" ),                         "ts", "tso", "tso" },
    { N_( "Turkish" ),                        "tr", "tur", "tur" },
    { N_( "Turkmen" ),                        "tk", "tuk", "tuk" },
    { N_( "Twi" ),                            "tw", "twi", "twi" },
    { N_( "Uighur" ),                         "ug", "uig", "uig" },
    { N_( "Ukrainian" ),                      "uk", "ukr", "ukr" },
    { N_( "Urdu" ),                           "ur", "urd", "urd" },
    { N_( "Uzbek" ),                          "uz", "uzb", "uzb" },
    { N_( "Vietnamese" ),                     "vi", "vie", "vie" },
    { N_( "Volapuk" ),                        "vo", "vol", "vol" },
    { N_( "Welsh" ),                          "cy", "cym", "wel" },
    { N_( "Wolof" ),                          "wo", "wol", "wol" },
    { N_( "Xhosa" ),                          "xh", "xho", "xho" },
    { N_( "Yiddish" ),                        "yi", "yid", "yid" },
    { N_( "Yoruba" ),                         "yo", "yor", "yor" },
    { N_( "Zhuang" ),                         "za", "zha", "zha" },
    { N_( "Zulu" ),                           "zu", "zul", "zul" },
    /* XXX psz_eng_name MUST be NULL on the last item as it is the stop condition */
    { NULL,                                   "",   "",    "" }
};
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    /* Custom VLC additions */
    LANG_CODE  ( N_("On Screen Display"),                                 "od", "osd", "osd" )
    LANG_CODE3 ( N_("Original audio"),                                          "qaa", "qaa" )
    LANG_CODE  ( N_("Hebrew"),                                            "iw", "heb", "heb" ) /* for old DVDs */

    /* End marker */
    LANG_CODE  ( NULL, "", "", "" )
};
#undef LANG_CODE
#undef LANG_CODE2
#undef LANG_CODE3
