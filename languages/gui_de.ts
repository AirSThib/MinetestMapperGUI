<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de_DE">
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../mainwindow.ui" line="14"/>
        <source>MinetestMapper GUI</source>
        <translation>MinetestMapper Grafische Benutzeroberfläche</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="35"/>
        <source>General</source>
        <translation>Generell</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="41"/>
        <source>Select World dir</source>
        <translation>Minetest Welt auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="77"/>
        <source>Output Image</source>
        <translation>Ausgangsbild</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="89"/>
        <source>Save as</source>
        <translation>Speichern unter</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="109"/>
        <source>Specify the map file name (mandatory)</source>
        <translation>Legen Sie den Ausgansbild Dateinamen fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="159"/>
        <source>Map-Limit</source>
        <translation>Karte eingrenzen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="322"/>
        <source>geometrymode</source>
        <translation>Geometriemodus</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="191"/>
        <source>pixel</source>
        <translation>Pixel</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="171"/>
        <location filename="../mainwindow.ui" line="1901"/>
        <source>block</source>
        <translation>Kartenblock (16x16x16)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="308"/>
        <source>fixed</source>
        <translation>Fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="227"/>
        <source>shrink</source>
        <translation>verkleinern</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="359"/>
        <source>Heightmap</source>
        <translation>Höhenkarte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="814"/>
        <source>Specify the nodes list for the height map</source>
        <translation>Legt die Liste für Höhenkarten-nodes fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="897"/>
        <location filename="../mainwindow.ui" line="917"/>
        <source>Specify the color definition file for the height map</source>
        <translation>Legt die Farbdefinitionsliste für die Höhenkarte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="870"/>
        <source>a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation type="unfinished">Eine Monochrome Karte wird erstellt. </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="876"/>
        <source>e.g. grey,black, #00FF00</source>
        <translation>z.B. grey, black, #00FF00</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="844"/>
        <source>If a color is given, a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation>Wenn eine Farbe festgelegt ist, wird eine Monochrome Karte in Schatten dieser farbe erstellt. Diese reicht von einer Tiefe von -128 bis 127.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="122"/>
        <source>Preview: </source>
        <translation>Vorschau: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="221"/>
        <source>Currently, shrinking is done with block granularity, and based on which blocks are in the database. As the database always contains a row or and column of empty, or partially empty blocks at the map edges, there will still be empty pixels at the edges of the map. Use --blockcolor to visualize these empty blocks.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="224"/>
        <source>Generate a map of at most the requested geometry. Shrink it to the smallest possible size that still includes the same information.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="165"/>
        <source>The requested geometry will be extended so that the map does not contain partial map blocks (of 16x16 nodes each). At least all pixels covered by the geometry will be in the map, but there may be up to 15 more in every direction.</source>
        <translation>Die gewählte Gometrie wird ausgedehnt, sodass die Karte nur ganze Kartenblöcke (16x16) einschließt. Alle Pixel der geometrie werden eingeschlossen, aber es können bis zu 15 Pixel mehr sein.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="168"/>
        <source>round the coodinates to a multiple of 16.</source>
        <translation>Rundet die Koordinaten auf ein vielfaches von 16.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="185"/>
        <source>A map of exactly the requested size is generated (after adjustments due to the &apos;shrink&apos; flag, or possible adjustments required by the scale factor).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="188"/>
        <source>interpret the coordinates with pixel granularity.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="178"/>
        <source>min-Y</source>
        <translation>Untere Höhengrenze</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="198"/>
        <location filename="../mainwindow.ui" line="335"/>
        <source>Specify the upper height limit for the map</source>
        <translation>Legt das Obere Höhenlimit für die Karte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="201"/>
        <source>max-Y</source>
        <translation>Obere Höhengrenze</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="332"/>
        <source>Nodes higher than this level will not be drawn. This can be used to avoid floating islands or floating artefacts from abscuring the world below.</source>
        <translation>Blöcke über diesem level werden nicht angezigt. Dies kann dazu verwendet werden um schwebende Inseln und andere gegenstände auszusortieren.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="237"/>
        <source>Any nodes below this level will not be drawn.</source>
        <translation>Alle Blöcke unterhalb dieses wertes werden nicht angezeigt.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="240"/>
        <source>Specify the lower height limit for the map</source>
        <translation>Legt das untere Höhenlimit für die Karte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="256"/>
        <source>e.g. -200,-100:200,200</source>
        <translation>z.B. -200,-100:200,200</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="302"/>
        <source>NOTE: If this flag is used, and no actual geometry is specified, this would result in a maximum-size map (65536 x 65536), which is currently not possible, and will fail, due to a bug in the drawing library.</source>
        <translation>&lt;b&gt;Achtung:&lt;/b&gt; Wenn dieser Parameter verwendet wird, ohne dass eine geometrie festgelegt ist wird eine Karte der Maximalen Größe (65536 x 65536) erstellt. Dies ist derzeit nicht möglich aufgrund eines fehlers der Zeichenbibliothek.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="305"/>
        <source>don&apos;t reduce the map size. What ever is specified using a geometry option, is what will be draw, even if partly or fully empty.</source>
        <translation>Kartengröße wird nicht reduziert. Alles was in der Geometrie festgelegt ist wird angezeigt, egal ob es leer ist.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="847"/>
        <source>Color</source>
        <translation>Farbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="854"/>
        <source>If no color is specified, minetestmapper will use a colors file to determine which colors to use at which height level.</source>
        <translation>Wenn keine Farbe festgelegt wurde, verwendet der minetestmapper eine datei.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="857"/>
        <source>File</source>
        <translation>Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="930"/>
        <source>use color or select a heightmap-colors.txt file</source>
        <translation>Verwende eine Farbe, oder wähle eine heightmap-colors.txt datei aus</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="940"/>
        <source>heightmap Skale</source>
        <translation>Höhenkarte Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="946"/>
        <location filename="../mainwindow.ui" line="949"/>
        <source>Draw a height scale at the bottom of the map</source>
        <translation>Zeichne eine Höhenskala am unteren Rand der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="952"/>
        <source>Draw Heightscale</source>
        <translation>Zeichne Höhenkartenskala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="992"/>
        <source>other</source>
        <translation>Weitere</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="998"/>
        <source>Y-scale</source>
        <translation>Y-Skalierung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1018"/>
        <source>Height level 0</source>
        <translation>Normal Null höhe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1056"/>
        <source>Colors</source>
        <translation>Farben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1062"/>
        <source>tilebordercolor</source>
        <translation>Rasterfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1069"/>
        <source>Specify the background color for the image</source>
        <translation>Legt die Hintergrundfarbe für das Bild fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1082"/>
        <source>bgcolor</source>
        <translation>Hintergrundfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1096"/>
        <source>playercolor</source>
        <translation>Spielerfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1103"/>
        <source>Specify the color for empty mapblocks</source>
        <translation>Legt die Farbe für leere kartenabschnitte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1113"/>
        <source>blockcolor</source>
        <translation>Farbe für leere Kartenabschnitte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1120"/>
        <source>origincolor</source>
        <translation>Farbe des Ursprungs</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1127"/>
        <source>scalecolor</source>
        <translation>Farbe der Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1231"/>
        <source>Specify the color for drawing tile borders</source>
        <translation>Legt die Farbe des Rasters fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1241"/>
        <source>Specify the color for drawing player locations</source>
        <translation>Legt die Farbe der Spielerpositionen fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1251"/>
        <source> Specify the color for drawing the map origin (0,0)</source>
        <translation>Legt die Farbe der Ursprungsmarkierung fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1261"/>
        <source> Specify the color for text in the scales on the side</source>
        <translation>Legt die Farbe des Textes in der Skala fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1272"/>
        <source>Map features</source>
        <translation>Eigenschaften</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1335"/>
        <source>Draw origin</source>
        <translation>zeichne Ursprung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1278"/>
        <source>Draw a scale on the left and/or top edge</source>
        <translation>Zeichnet eine Skala links und/oder oben auf der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1281"/>
        <source>drawscale</source>
        <translation>Zeichne Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2362"/>
        <source>edit colors.txt</source>
        <translation>bearbeite colors.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2370"/>
        <source>edit heightmap-nodes.txt</source>
        <translation>bearbeite heightmap-nodes.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2378"/>
        <source>edit heightmap-colors.txt</source>
        <translation>bearbeite heightmap-colors.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1332"/>
        <source> Draw a circle at the origin (0,0) on the map</source>
        <translation>Zeichne ein Kreis am Mittelpunkt (0,0) auf der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1359"/>
        <source>Enable drawing transparency for some nodes (e.g. water)</source>
        <translation>Zeichnet Transparenz z.B. für Wasser</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1342"/>
        <source>Draw circles at player positions on the map</source>
        <translation>Zeichet kreise bei den Spielerpositionen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1345"/>
        <source>Draw Players</source>
        <translation>Zeichne Spielerpossitionen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1389"/>
        <source>Draw air nodes (read the warnings first!)</source>
        <translation>Macht Luft sichtbar (bitte zuerst die Warnungen lesen)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1399"/>
        <source>Disable shading that accentuates height diffences</source>
        <translation>Deaktiviert die Schatten der Höhenunterschiede</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1295"/>
        <source>top</source>
        <translation>Oben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2148"/>
        <source>&amp;Edit</source>
        <translation>&amp;Bearbeiten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2184"/>
        <source>Main Toolbar</source>
        <translation>Hauptwerkzeugleiste</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2233"/>
        <source>qrc:/doc/intro.html</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2315"/>
        <source>Whats this?</source>
        <translation>Was ist das?</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2327"/>
        <source>Open World</source>
        <translation>Öffne Welt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2339"/>
        <source>Save map as</source>
        <translation>Speichere karte als</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1288"/>
        <source>left</source>
        <translation>Links</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1352"/>
        <source>Draw Alpha</source>
        <translation>Durchsichtiges Wasser</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1392"/>
        <source>Draw Air</source>
        <translation>Zeichne Luft</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1402"/>
        <source>No Shading</source>
        <translation>Keine Schatten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="365"/>
        <source>Generate a height map instead of a regular map</source>
        <translation>Erstellt eine Höhenkarte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="368"/>
        <source> Generate a height map instead of a regular map</source>
        <translation>Eine Höhenkarte anstatt einer normalen erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="808"/>
        <source>Heightmap nodes</source>
        <translation type="unfinished">Höhenkarte Nodes</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="63"/>
        <location filename="../mainwindow.ui" line="824"/>
        <location filename="../mainwindow.ui" line="900"/>
        <location filename="../mainwindow.ui" line="1220"/>
        <source>browse</source>
        <translation>Durchsuchen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="47"/>
        <source>Select the world directory, wich contains the world Database</source>
        <translation>Wählen Sie den Welt-ordner aus, der die Datenbank enthält</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="100"/>
        <location filename="../mainwindow.ui" line="129"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;
&lt;p&gt;you can use placeholders in the filename:&lt;/p&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;isodate&amp;gt;&lt;/span&gt; is replaced with the current date&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;world&amp;gt;&lt;/span&gt; is replaced with the worldname&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;date&amp;gt;&lt;/span&gt; is replaced with local date format&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;longdate&amp;gt;&lt;/span&gt; is replaced with the local spoken date format&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;time&amp;gt;&lt;/span&gt; is replaced with current time&lt;br&gt;also something like D:/&amp;lt;world&amp;gt;/&amp;lt;isodate&amp;gt;.png is possible.&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;
&lt;p&gt;Folgende Platzhalter für den Ausgangsbild Dateinamen sind möglich:&lt;/p&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;isodate&amp;gt;&lt;/span&gt; wird ersetzt mit dem aktuellen ISO-Datum&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;world&amp;gt;&lt;/span&gt;wird ersetzt mit dem aktuellem welt-namen&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;date&amp;gt;&lt;/span&gt; wird mit dem lokalem Datum ersetzt z.B. 15.05.2015&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;longdate&amp;gt;&lt;/span&gt;wird mit dem langen lokalen Datum ersetzt z.B. Freitag,15. Mai 2015&lt;br&gt;
&lt;span style=&quot; font-weight:600;&quot;&gt;&amp;lt;time&amp;gt;&lt;/span&gt; wird mit der aktuellen Uhrzeit ersetzt&lt;br&gt;auch Pfadangaben wie z.B. D:/&amp;lt;world&amp;gt;/&amp;lt;isodate&amp;gt;.png sind möglich.&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="115"/>
        <source>map.png</source>
        <translation>karte.png</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="295"/>
        <source>scalefactor</source>
        <translation>Skalierfaktor</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="315"/>
        <source>geometry</source>
        <translation>Geometrie</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="348"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;geometry-syntax&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#0000ff;&quot;&gt;help&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="838"/>
        <source>Heightmap colors</source>
        <translation>Höhenkarte Farben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="883"/>
        <location filename="../mainwindow.ui" line="1154"/>
        <location filename="../mainwindow.ui" line="1165"/>
        <location filename="../mainwindow.ui" line="1176"/>
        <location filename="../mainwindow.ui" line="1187"/>
        <location filename="../mainwindow.ui" line="1198"/>
        <location filename="../mainwindow.ui" line="1209"/>
        <location filename="../mainwindow.cpp" line="672"/>
        <location filename="../mainwindow.cpp" line="684"/>
        <location filename="../mainwindow.cpp" line="696"/>
        <location filename="../mainwindow.cpp" line="708"/>
        <location filename="../mainwindow.cpp" line="721"/>
        <location filename="../mainwindow.cpp" line="733"/>
        <location filename="../mainwindow.cpp" line="777"/>
        <source>select color</source>
        <translation>Farbe auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="962"/>
        <source>custom heightscale intervall</source>
        <translation>Benuzerdefinierte Höhenskalaeinteilung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="972"/>
        <location filename="../mainwindow.ui" line="1315"/>
        <source>Major: </source>
        <translation>Hauptskalierung: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="982"/>
        <location filename="../mainwindow.ui" line="1325"/>
        <source>Minor: </source>
        <translation>Nebenskalierung: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1134"/>
        <source>colors.txt file</source>
        <translation>colors.txt Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1305"/>
        <source>custom sidescale Interval</source>
        <translation>Benutzerdefinierte Skaleneinteilung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1410"/>
        <source>Tiles</source>
        <translation>Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1416"/>
        <source>Draw tiles</source>
        <translation>Zeichne Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1859"/>
        <source>tiles</source>
        <translation>Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1868"/>
        <source>size: </source>
        <translation>Größe: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1887"/>
        <source>chunk</source>
        <translation>Kartengeneratorblock (5x5x5)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1894"/>
        <source>tilesize+border</source>
        <translation>Größe+Rahmen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1914"/>
        <source>border: </source>
        <translation>Rahmen: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1930"/>
        <source>arrange</source>
        <translation>Ausrichten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1936"/>
        <source>tilecenter</source>
        <translation>Zentrieren</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1943"/>
        <source>tileorigin</source>
        <translation>Ursprung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1953"/>
        <source>arrange at</source>
        <translation>Ausrichten an</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1959"/>
        <source>coordinates</source>
        <translation>Koordinaten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1966"/>
        <source>world</source>
        <translation>Welt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1976"/>
        <source>map</source>
        <translation>Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2039"/>
        <source>MinetestMapper Output</source>
        <translation>Ausgabe des minetestmapper</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2062"/>
        <source>select all</source>
        <translation>Alles auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2069"/>
        <source>copy</source>
        <translation>In Zwischenablage kopiern</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2076"/>
        <source>clear</source>
        <translation>leeren</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2097"/>
        <source>Generate</source>
        <translation>Erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2111"/>
        <source>Cancel</source>
        <translation>Abbrechen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2130"/>
        <source>&amp;File</source>
        <translation>&amp;Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2134"/>
        <source>Choose profile:</source>
        <translation>Profil auswählen:</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2157"/>
        <location filename="../mainwindow.ui" line="2209"/>
        <location filename="../mainwindow.ui" line="2307"/>
        <source>Help</source>
        <translation>Hilfe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2167"/>
        <source>Language</source>
        <translation>Sprache</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2172"/>
        <source>Extras</source>
        <translation>Extras</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2252"/>
        <location filename="../mainwindow.cpp" line="758"/>
        <source>About MinetestMapper</source>
        <translation>Über MinetestMapper</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2263"/>
        <source>About QT</source>
        <translation>Über QT</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2278"/>
        <source>generate Map</source>
        <translation>Karte Erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2281"/>
        <source>starting Minetestmapper to generate the map</source>
        <translation>startet den Minetestmapper um die Karte zu erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2284"/>
        <source>generate the Map</source>
        <translation>erstellt die Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2292"/>
        <source>Exit</source>
        <translation>Beenden</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2383"/>
        <location filename="../mainwindow.cpp" line="790"/>
        <source>New Profile</source>
        <translation>Neues Profil</translation>
    </message>
    <message>
        <source>Default</source>
        <translation type="vanished">Standart</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2391"/>
        <location filename="../mainwindow.cpp" line="303"/>
        <source>Expert Mode</source>
        <translation>Expertenmodus</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2394"/>
        <source>In the Expert Mode it shows you the parameters, that you can modify it.</source>
        <translation>Im Expertenmodus wird ein Fenster mit den Parametern geöfnet. Die Parameter können dann Manuell verändert werden.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2397"/>
        <source>Expert Mode shows the parameters, that you can modify it.</source>
        <translation>Im Expertenmodus werden die Parameter angezeigt, die du verändern kannst.</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="107"/>
        <source>Current Language changed to %1</source>
        <translation>Sprache wurde auf %1 geändert</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2351"/>
        <location filename="../mainwindow.cpp" line="744"/>
        <source>About MinetestMapper GUI</source>
        <translation>Über MinetestMapperGUI</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="141"/>
        <source>no input world selected</source>
        <translation>Keine Minetestwelt ausgewählt</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="142"/>
        <source>ERROR: No MinetestWorld selected&lt;br&gt;&lt;br&gt;please select a world</source>
        <translation>FEHLER: Keine Minetestwelt ausgewählt&lt;br&gt;&lt;br&gt;Bitte wähle eine Welt aus</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="148"/>
        <source>no output image selected</source>
        <translation>Kein Ausgabebild ausgewählt</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="149"/>
        <source>ERROR: No output image selected&lt;br&gt;&lt;br&gt;please select a output image</source>
        <translation>FEHLER: Kein Ausgabebild Ausgewählt. &lt;br&gt;&lt;br&gt;Bitte ein Bild Auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="154"/>
        <source>the Image File does already exist</source>
        <translation>Das Bild existiert bereits</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="155"/>
        <source>The File &lt;i&gt;%1&lt;/i&gt; does already exist. &lt;br&gt;&lt;br&gt;Do you want to overwrite?</source>
        <translation>Die Datei &lt;i&gt;%1&lt;/i&gt; existiert bereits. &lt;br&gt;&lt;br&gt;Soll die Datei Überschrieben werden?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="164"/>
        <source>the directory does not exist</source>
        <translation>Der Ordner existiert nicht</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="165"/>
        <source>The directory &lt;i&gt;%1&lt;/i&gt; does not exist. &lt;br&gt;&lt;br&gt;Should it be created?</source>
        <translation>Der Ordner &lt;i&gt;%1&lt;/i&gt; existiert nicht. &lt;br&gt;&lt;br&gt;Möchten sie den Ordner erstellen?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="304"/>
        <source>MinetestMapper will be executed using this arguments. 
The arguments can be removed, modified, or new arguments can be added.</source>
        <translation>MinetestMapper wird mit den folgenden Parametern ausgeführt. 
Die einzelnen Parameter können entfernt, verändert, oder neue hinzugefügt werden.</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="397"/>
        <source>Finisched :)</source>
        <translation>Fertig :-)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="402"/>
        <source>minetestmapper terminated</source>
        <translation>minetestmapper abgebrochen</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="405"/>
        <location filename="../mainwindow.cpp" line="420"/>
        <source>Minetest Mapper failed</source>
        <translation>Minetestmapper hat ein Fehler festgestellt</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="406"/>
        <source>&lt;h1&gt;ERROR&lt;/h1&gt; &lt;h2&gt;minetestmapper failed&lt;/h2&gt;Exit code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Status of MinetestMapper: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;&lt;br&gt;Please fix the error and try again </source>
        <translation>&lt;h1&gt;Fehler&lt;/h1&gt; &lt;h2&gt;kartenerstellung fehlgeschlagen&lt;/h2&gt;Exit code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Ausgabe des Minetstmapper: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;&lt;br&gt;Bitte den Fehler beheben und erneut versuchen </translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="421"/>
        <source>&lt;h1&gt;ERROR&lt;/h1&gt; &lt;h2&gt;minetestmapper failed&lt;/h2&gt;Error code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Error Message: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;</source>
        <translation>&lt;h1&gt;FEHLER&lt;/h1&gt; &lt;h2&gt;minetestmapper ist abgestürzt&lt;/h2&gt;Fehlercode: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Fehlernachricht: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="630"/>
        <source>Open Minetest World</source>
        <translation>Minetest Welt-Ordner öffnen</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="640"/>
        <source>Save generated map to...</source>
        <translation>Karte speichern nach...</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="640"/>
        <source>png image (*.png)</source>
        <translation>png Grafik (*.png)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="647"/>
        <source>Open HeightmapNodes File</source>
        <translation>Öffne HeightmapNodes Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="649"/>
        <location filename="../mainwindow.cpp" line="657"/>
        <location filename="../mainwindow.cpp" line="665"/>
        <source>TXT File (*.txt)</source>
        <translation>TXT Datei (*.txt)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="655"/>
        <source>Open HeightmapColors File</source>
        <translation>Öffne Höhenkarte Farbdefinitionsdatei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="663"/>
        <source>Open colors.txt File</source>
        <translation>Öffne colors.txt Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="745"/>
        <source>&lt;h1&gt;About MinetestMapperGUI&lt;/h1&gt;The &lt;b&gt;MinetestMapper Gui&lt;/b&gt; is written by addi.&lt;br /&gt;It is licensed under a &lt;a href=&quot;http://creativecommons.org/licenses/by/3.0/&quot;&gt;Creative Commons Attribution 3.0 Unported License&lt;/a&gt;.&lt;br&gt;The current version is %1.%2.%3. &lt;br&gt;The sourcecode is aviable on &lt;a href=&apos;https://bitbucket.org/adrido/minetestmappergui/&apos;&gt;Bitbucket&lt;/a&gt;.&lt;br&gt;You may also want to read the &lt;a href=&apos;https://forum.minetest.net/viewtopic.php?f=14&amp;t=12139&apos;&gt;Minetest forum thread&lt;/a&gt;.&lt;br&gt;&lt;br&gt;&lt;b&gt;Thanks to:&lt;/b&gt;&lt;br&gt;McKrustenkaese for his great icon</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="759"/>
        <source>&lt;h1&gt;About MinetestMapper&lt;/h1&gt;The &lt;b&gt;MinetestMapper&lt;/b&gt; is written by:&lt;br&gt;Miroslav Bendík &lt;miroslav.bendik@gmail.com&gt;&lt;br&gt;ShadowNinja &lt;shadowninja@minetest.net&gt;&lt;br&gt;sfan5 &lt;sfan5@live.de&gt;&lt;br&gt;Rogier &lt;rogier777@gmail.com&gt;&lt;br&gt;&lt;br&gt;&lt;u&gt;License:&lt;/u&gt;LGPLv2.1+ and BSD 2-clause.&lt;br&gt;&lt;u&gt;Source Code:&lt;/u&gt; &lt;a href=&apos;https://github.com/Rogier-5/minetest-mapper-cpp&apos;&gt;Github&lt;/a&gt;&lt;br&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="771"/>
        <source>preview: %1</source>
        <translation>Vorschau: %1</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="791"/>
        <source>Name of the new Profile:</source>
        <translation type="unfinished">Name des Neuen Profils:</translation>
    </message>
</context>
</TS>
