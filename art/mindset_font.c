/**
 * Transform 1-bit font data into 4bpp data
 */

#include <stdio.h>

const unsigned char fontdata_mono[] =
  {
"                                                                                                                                                                  ....    ....                                                                                                  .....                     .. ..   .. .. .......    ......   .........    .......   ......                          ...      ..    .....   ......    ...  ......    ....  .......  ....    .....        .        ........       ..........                  ...   ......    ....  .....    ...... .......   ..... ..   ..  ......      .. ..   ..  ..     ..   .. ..   ..  .....  ......   .....  ......   ....    ...... ..   .. ..   .. ..   .. ..   ..  ..  .. .......    ...   ....                                         .         .......        ........             ...        ........           .....            ....                                                                                                                                                           .   ......  ......  ......  ..   ..   .   ..        ...   ..       .....  ..       .....  ..   ..   ..                               . ..      .....                 .....     ......                ......    ......                .....     ... ..                ......    ......                ......     .....                .....     ......                ..            .                   ............   .. ...  ... ..                                                                                                                                                                                                                 ....        ....    .  ..  .        .  ..  .        .  ..  .           ..       ................                                      .  .                                                         .        .      .        .                   .  .        .  .                                   .        .                              .        .   ................                        "
"   ...      ..    .....   ......    ...  ......    ....  .......  ....    .....    ...   ......    ....  .....    ...... .......                                 ......  ......                                                                                                 .....                     .. ..   .. .. ........   .......  ..........  ........  ........                        .  ..    ...   ..   ..     ..    ....  ..       ..     ..   .. ..   .  ..   ..      .                .       ..       .                 .. ..  ..   ..  ..  .. ..  ..   ..     ..       ..     ..   ..    ..        .. ..  ..   ..     ... ... ...  .. ..   .. ..   .. ..   .. ..   .. ..  ..     ..   ..   .. ..   .. ..   .. ... ...  ..  ..     ...    ...  .    .                                        .         .......        ........             ...        ........           .....           .....                                                                                                                                                          ..  .    .  . .     . .   . .  . .  . ..  .  .      .   . .  .         .  .  .      .     .  . .  . .  .                              . ...     .... .                ....       .....                ......    ......                .....     ......                ......    ......             .  ......     .....                 ...       ... .                .             .                   ............   .   ..  ..   .                                                                                                                                                                                                                     ..    ..        .  ..  .        .  ..  .        .  ..  .           ..                                                             .  .                                                         .        .      .        .                      .        .                                      .        .                              .        .                                           "
"  .  ..    ...   ..   ..     ..    ....  ..       ..     ..   .. ..   .  ..   ..  .. ..  ..   ..  ..  .. ..  ..   ..     ..                        ..      ..   ................                                                                                             .......                       .  .    .  . ..    ..        ..  ..  ..  ..  ..        ..    ..                       ..   ..    ..       ...    ..    .. ..  ......  ..          ..  ...  .  ..   ..     .                 .       ..       .                ..   .. ..   .. ..      ..   ..  ..     ..      ..      ..   ..    ..        .. .. ..    ..     ....... .... .. ..   .. ..   .. ..   .. ..   .. ..         ..   ..   .. ..   .. .. . ..  .....   ..  ..    ...    ...  .  ..  .....  .....  ....                      . ....    .........      ........     ...     ...        ........   ....    .....         .......                                                                                                                                                           .  .   .   . ....  .    .  .  . .  .  .  .  .      .   . .  .        .   .  .      ....  .  . .  . .  .                              .....     .... .               .....       ..... ..             ......    .......              .......    .. ....               .....      ........           ........     .....                 ..         .. ..            ...              .                  ..............                                                                                                                                                                                                                                       .  .          .  ..  .        .  ..  .        .  ..  .           ..                                                           ..    ..                                                       .        .     .          .                     .        .                                      .        .                             .          .                                          "
" ..   ..    ..       ...    ..    .. ..  ......  ..          ..  ...  .  ..   .. ..   .. ..   .. ..      ..   ..  ..     ..        ..      ..     ....    ....  ................                                                                                            .......                       .  .    .  .  ..    ..  ........  ..  ..  ..  ..        ..    ..                       ..   ..    ..     ....    ....  ..  ..       .. ......     ..    ....    ......    .      ...         .       ..       .                ..   .. ......  ..      ..   ..  .....  ......  ..  ... .......    ..        .. ....     ..     ....... ....... ..   .. ..   .. ..   .. ..   ..  .....     ..   ..   .. ... ... .......   ...     ....    ...     ..   . .    ..   .   .   .                            ....           ...                  ...                           .....                                                                                                                                                                                   .  .    .  .     . .    .  .  . .  .  .  .  .         .  .  .         .  .  .          . .  . .  . .  .                              .....      ... ....         ......          .........          ......      ..... ..          .. ......    .. ... ...            .....      ......               .....       ....               . .           . . ..         ..  .             .                  ..............                                                                                                                                                                                                                                 ...   .  .   ...    .  ..  .       .   ..   .      .   ..   .   ...    ..    ...................                                ....        ....                ................                   .        .   ..            ..                ....        ....                     ......         .      .                            ..            ..     ......                             "
" ..   ..    ..     ....    ....  ..  ..       .. ......     ..    ....    ...... ..   .. ......  ..      ..   ..  .....  ......    ..      ..     ....    ....  ................                                                                                           .......                                      ..    ..  ........  ..  ..  ..  ..        ..    ..                       ..   ..    ..    ....        .. .......      .. ..   ..   ..    .  ....      ..   .                   .       ..       .                ....... ..   .. ..      ..   ..  ..     ..      ..   .. ..   ..    ..        .. .....    ..     .. . .. .. .... ..   .. ......  .. .... .....        ..    ..   ..   ..  .....  .......  .....     ..    ...      .    . .    .....    .    ...                         .....          ....                 ...        .                  .....                                                                                                                                                                                   .  .     . .     . .   .   .  . .  .  .  .  .        .   .  .          . .  .          . .  . .  . .  .                              .....           ....       .......           ... ...           ......      .........        ..........    ...........      ... .....        ......             ......       .....   .     .   ..               ....         ......            .       ....       ..............                                                                                                                                                                                                                                    .   ..   .       .  ..  .    ...   .  .   ......    ..    ...   .   ..   .                   ................................                ....        ....                ..            ..   .        .                   ....        ....                ................    .      .         ......             ..            ..                    .      .                            "
" ..   ..    ..    ....        .. .......      .. ..   ..   ..    .  ....      .. ....... ..   .. ..      ..   ..  ..     ..                        ..      ..   ................                                                                                             ...                 ..                     ..    ..  ..    ..  ..  ..  ..  ..        ..    ..                        ..  .     ..   ...     ..   ..     ..  ..   .. ..   ..   ..    .    ..     ..   .                    .       ..       .                ..   .. ..   ..  ..  .. ..  ..   ..     ..       ..  .. ..   ..    ..   ..   .. .. ...   ..     ..   .. ..  ... ..   .. ..      ..  ..  .. ...  ..   ..    ..   ..   ..   ...   ... ... ... ...    ..   ...            .  ..  ..       .       .                        ......         ......               ...        ...                .....                                                                                                                                                                                   .  . .   . . .   . .   .   .  . .  .  .  .  .       .    .  .      .   . .  .      .   . .  . .  . .  .                              ....            .....     ......               .....        .......          .......        .. .......    ............    .........          .. ....         .......         .....  .     .  ...               ....         .....             .     ........     ..............                                                                                                                                                                                                                 ................    .  ..  .        .  ..  .          .  .             ..           .  ..  .                                                                        ..    ..                      .          .     .        .                      .        .                   .              .   .        .                             .          .                     .        .                           "
"  ..  .     ..   ...     ..   ..     ..  ..   .. ..   ..   ..    .    ..     ..  ..   .. ..   ..  ..  .. ..  ..   ..     ..                                      ......  ......                                                                                                .                 ..                     ..    ..  ........  ..  ..  ..  ........  ........                         ...    ...... .......  .....      ..   .....   .....    ..     .....   ....   .                     .       ..       .                ..   .. ......    ....  .....    ...... ..        ..... ..   ..  ......  .....  ..  ...  ...... ..   .. ..   ..  .....  ..       .... . ..  ...  .....     ..    .....     .    ..   .. ..   ..    ..   .......  .      .    . .       .   ....                         .......        ........             ...        ........           .....               .                                                                                                                                                                  ...  . ...   . ...   .  .    ..   ..  ...  ..       .....  ..        ...   ..        ...   ..   ..   ..                          ...                  .....     ......                .....      .....                ....        . .......      ...........    ......                .....       ......             ......     ......                ...         ....               .   ..........    ..............                                                                                                                                                                                                                 ................    .  ..  .        .  ..  .        ..    ..           ..           .  ..  .                                                                          .  .                         .        .      .        .                      .        .                   .              .   .        .                              .        .                      .        .                           "
"   ...    ...... .......  .....      ..   .....   .....    ..     .....   ....   ..   .. ......    ....  .....    ...... ..                                       ....    ....                                                                                                                                          ..    ..  ........  ..  ..  ..   .......   ......                                                                                                                              ..........       ........                                                                                                                                                                                                                                  ....                                 .         .......        ........             ...        ........           .....              ..                                                                                                                                                                                                                                                                                                  ... ..                .....     ......                ......    ......                .....      .. ..                ......    ......                .....       ....                .....     ......                .             .                   ............   ..............                                                                                                                                                                                                                                     .  ..  .        .  ..  .    ....        ....       ..           .  ..  .                    ................                                      .  .                         .        .      .        .                   .  .        .  .                ................   .        .                              .        .                      .        .                           "
  };
int main(int argc, char* argv[])
{
  int len=sizeof(fontdata_mono);
  int i;

  printf("unsigned char fontdata[]={\n");
  
  while (i<len)
    {
      printf("  0x");
      if (fontdata_mono[i]==' ')
	printf("0");
      else if (fontdata_mono[i]=='.')
	printf("F");
      if (fontdata_mono[i+1]==' ')
	printf("0");
      else if (fontdata_mono[i+1]=='.')
	printf("F");
      printf(", ");
      i+=2;
    }

  printf("\n");
  printf("};\n");

  printf("len: %d\n",i);
  
  return 0;
}