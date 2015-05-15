<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en_US">
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../mainwindow.ui" line="14"/>
        <source>MinetestMapper GUI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="38"/>
        <source>General</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="44"/>
        <source>Select World dir</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="62"/>
        <source>Select the world directory, wich contains the world Database</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="78"/>
        <location filename="../mainwindow.ui" line="847"/>
        <location filename="../mainwindow.ui" line="929"/>
        <location filename="../mainwindow.ui" line="1251"/>
        <source>browse</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="92"/>
        <source>Output Image</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="104"/>
        <source>Save as</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="130"/>
        <source>Specify the map file name (mandatory)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="136"/>
        <source>map.png</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="180"/>
        <source>Map-Limit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="316"/>
        <source>scalefactor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="336"/>
        <source>geometry</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="343"/>
        <source>geometrymode</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="212"/>
        <source>pixel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="192"/>
        <location filename="../mainwindow.ui" line="1944"/>
        <source>block</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="329"/>
        <source>fixed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="248"/>
        <source>shrink</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="143"/>
        <source>Preview: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="242"/>
        <source>Currently, shrinking is done with block granularity, and based on which blocks are in the database. As the database always contains a row or and column of empty, or partially empty blocks at the map edges, there will still be empty pixels at the edges of the map. Use --blockcolor to visualize these empty blocks.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="245"/>
        <source>Generate a map of at most the requested geometry. Shrink it to the smallest possible size that still includes the same information.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="186"/>
        <source>The requested geometry will be extended so that the map does not contain partial map blocks (of 16x16 nodes each). At least all pixels covered by the geometry will be in the map, but there may be up to 15 more in every direction.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="189"/>
        <source>round the coodinates to a multiple of 16.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="206"/>
        <source>A map of exactly the requested size is generated (after adjustments due to the &apos;shrink&apos; flag, or possible adjustments required by the scale factor).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="209"/>
        <source>interpret the coordinates with pixel granularity.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="199"/>
        <source>min-Y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="219"/>
        <location filename="../mainwindow.ui" line="356"/>
        <source>Specify the upper height limit for the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="222"/>
        <source>max-Y</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="353"/>
        <source>Nodes higher than this level will not be drawn. This can be used to avoid floating islands or floating artefacts from abscuring the world below.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="258"/>
        <source>Any nodes below this level will not be drawn.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="261"/>
        <source>Specify the lower height limit for the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="277"/>
        <source>e.g. -200,-100:200,200</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="323"/>
        <source>NOTE: If this flag is used, and no actual geometry is specified, this would result in a maximum-size map (65536 x 65536), which is currently not possible, and will fail, due to a bug in the drawing library.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="326"/>
        <source>don&apos;t reduce the map size. What ever is specified using a geometry option, is what will be draw, even if partly or fully empty.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="373"/>
        <source>Heightmap</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="379"/>
        <source>Generate a height map instead of a regular map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="382"/>
        <source> Generate a height map instead of a regular map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="831"/>
        <source>Heightmap nodes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="837"/>
        <source>Specify the nodes list for the height map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="861"/>
        <source>Heightmap colors</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="867"/>
        <source>If a color is given, a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="870"/>
        <source>Color</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="877"/>
        <source>If no color is specified, minetestmapper will use a colors file to determine which colors to use at which height level.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="880"/>
        <source>File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="893"/>
        <source>a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="899"/>
        <source>e.g. grey,black, #00FF00</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="906"/>
        <location filename="../mainwindow.ui" line="1185"/>
        <location filename="../mainwindow.ui" line="1196"/>
        <location filename="../mainwindow.ui" line="1207"/>
        <location filename="../mainwindow.ui" line="1218"/>
        <location filename="../mainwindow.ui" line="1229"/>
        <location filename="../mainwindow.ui" line="1240"/>
        <location filename="../mainwindow.cpp" line="528"/>
        <location filename="../mainwindow.cpp" line="540"/>
        <location filename="../mainwindow.cpp" line="552"/>
        <location filename="../mainwindow.cpp" line="564"/>
        <location filename="../mainwindow.cpp" line="577"/>
        <location filename="../mainwindow.cpp" line="589"/>
        <location filename="../mainwindow.cpp" line="629"/>
        <source>select color</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="926"/>
        <location filename="../mainwindow.ui" line="946"/>
        <source>Specify the color definition file for the height map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="959"/>
        <source>use color or select a heightmap-colors.txt file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="969"/>
        <source>heightmap Skale</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="975"/>
        <location filename="../mainwindow.ui" line="978"/>
        <source>Draw a height scale at the bottom of the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="981"/>
        <source>Draw Heightscale</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="988"/>
        <location filename="../mainwindow.ui" line="1379"/>
        <source>Major</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1004"/>
        <location filename="../mainwindow.ui" line="1363"/>
        <source>Minor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1023"/>
        <source>other</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1029"/>
        <source>Y-scale</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1049"/>
        <source>Height level 0</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1087"/>
        <source>Colors</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1093"/>
        <source>tilebordercolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1100"/>
        <source>Specify the background color for the image</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1113"/>
        <source>bgcolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1127"/>
        <source>playercolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1134"/>
        <source>Specify the color for empty mapblocks</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1144"/>
        <source>blockcolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1151"/>
        <source>origincolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1158"/>
        <source>scalecolor</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1165"/>
        <source>colors.txt file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1262"/>
        <source>Specify the color for drawing tile borders</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1272"/>
        <source>Specify the color for drawing player locations</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1282"/>
        <source> Specify the color for drawing the map origin (0,0)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1292"/>
        <source> Specify the color for text in the scales on the side</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1303"/>
        <source>Map features</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1312"/>
        <source>Draw origin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1438"/>
        <source>Draw a scale on the left and/or top edge</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1441"/>
        <source>drawscale</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2332"/>
        <source>edit colors.txt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2340"/>
        <source>edit heightmap-nodes.txt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2348"/>
        <source>edit heightmap-colors.txt</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1309"/>
        <source> Draw a circle at the origin (0,0) on the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1395"/>
        <source>Enable drawing transparency for some nodes (e.g. water)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1319"/>
        <source>Draw circles at player positions on the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1322"/>
        <source>Draw Players</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1356"/>
        <source>Draw Alpha</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1336"/>
        <source>Draw air nodes (read the warnings first!)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1339"/>
        <source>Draw Air</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1346"/>
        <source>Disable shading that accentuates height diffences</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1349"/>
        <source>No Shading</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1448"/>
        <source>left</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1329"/>
        <source>top</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="121"/>
        <location filename="../mainwindow.ui" line="150"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;
&lt;p&gt;you can use placeholders in the filename:&lt;/p&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;isodate&amp;gt;&lt;/span&gt; is replaced with the current date&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;world&amp;gt;&lt;/span&gt; is replaced with the worldname&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;date&amp;gt;&lt;/span&gt; is replaced with local date format&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;longdate&amp;gt;&lt;/span&gt; is replaced with the local spoken date format&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;time&amp;gt;&lt;/span&gt; is replaced with current time&lt;br&gt;also something like D:/&amp;lt;world&amp;gt;/&amp;lt;isodate&amp;gt;.png is possible.&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1456"/>
        <source>Tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1462"/>
        <source>Draw tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1902"/>
        <source>tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1911"/>
        <source>size: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1930"/>
        <source>chunk</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1937"/>
        <source>tilesize+border</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1957"/>
        <source>border: </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1973"/>
        <source>arrange</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1979"/>
        <source>tilecenter</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1986"/>
        <source>tileorigin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1996"/>
        <source>arrange at</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2002"/>
        <source>coordinates</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2009"/>
        <source>world</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2019"/>
        <source>map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2082"/>
        <source>MinetestMapper Output</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2099"/>
        <source>Generate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2120"/>
        <source>&amp;File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2130"/>
        <source>&amp;Edit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2139"/>
        <location filename="../mainwindow.ui" line="2187"/>
        <location filename="../mainwindow.ui" line="2281"/>
        <source>Help</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2149"/>
        <source>Language</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2159"/>
        <source>Main Toolbar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2211"/>
        <source>qrc:/doc/intro.html</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2226"/>
        <location filename="../mainwindow.cpp" line="610"/>
        <source>About MinetestMapper</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2237"/>
        <source>About QT</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2252"/>
        <source>generate Map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2255"/>
        <source>starting Minetestmapper to generate the map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2258"/>
        <source>generate the Map</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2266"/>
        <source>Exit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2289"/>
        <source>Whats this?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2301"/>
        <source>Open World</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2313"/>
        <source>Save map as</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2321"/>
        <location filename="../mainwindow.cpp" line="600"/>
        <source>About MinetestMapper GUI</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="104"/>
        <source>Current Language changed to %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="140"/>
        <source>the Image File does already exist</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="141"/>
        <source>The File &lt;i&gt;%1&lt;/i&gt; does already exist. &lt;br&gt;&lt;br&gt;Do you want to overwrite?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="150"/>
        <source>the directory does not exist</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="151"/>
        <source>The directory &lt;i&gt;%1&lt;/i&gt; does not exist. &lt;br&gt;&lt;br&gt;Should it be created?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="335"/>
        <source>Finisched :)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="340"/>
        <source>Minetest Mapper failed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="341"/>
        <source>&lt;h1&gt;ERROR&lt;/h1&gt; &lt;h2&gt;minetestmapper failed&lt;/h2&gt;Exit code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Status of MinetestMapper: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;&lt;br&gt;Please fix the error and try again </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="486"/>
        <source>Open Minetest World</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="496"/>
        <source>Save generated map to...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="496"/>
        <source>png image (*.png)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="503"/>
        <source>Open HeightmapNodes File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="505"/>
        <location filename="../mainwindow.cpp" line="513"/>
        <location filename="../mainwindow.cpp" line="521"/>
        <source>TXT File (*.txt)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="511"/>
        <source>Open HeightmapColors File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="519"/>
        <source>Open colors.txt File</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="601"/>
        <source>&lt;h1&gt;About MinetestMapperGUI&lt;/h1&gt;The &lt;b&gt;MinetestMapper Gui&lt;/b&gt; is written by addi &lt;br&gt;version %1.%2.%3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="611"/>
        <source>&lt;h1&gt;About MinetestMapper&lt;/h1&gt;The &lt;b&gt;MinetestMapper&lt;/b&gt; is written by:&lt;br&gt;Miroslav Bendík &lt;miroslav.bendik@gmail.com&gt;&lt;br&gt;ShadowNinja &lt;shadowninja@minetest.net&gt;&lt;br&gt;sfan5 &lt;sfan5@live.de&gt;&lt;br&gt;Rogier &lt;rogier777@gmail.com&gt;&lt;br&gt;&lt;br&gt;&lt;u&gt;License:&lt;/u&gt;LGPLv2.1+ and BSD 2-clause.&lt;br&gt;Source Code: &lt;a href=&apos;https://github.com/Rogier-5/minetest-mapper-cpp&apos;&gt;Github&lt;/a&gt;&lt;br&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="623"/>
        <source>preview: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
