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
        <location filename="../mainwindow.ui" line="38"/>
        <source>General</source>
        <translation>Generell</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="44"/>
        <source>Select World dir</source>
        <translation>Minetest Welt auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="80"/>
        <source>Output Image</source>
        <translation>Ausgangsbild</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="92"/>
        <source>Save as</source>
        <translation>Speichern unter</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="112"/>
        <source>Specify the map file name (mandatory)</source>
        <translation>Legen Sie den Ausgansbild Dateinamen fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="162"/>
        <source>Map-Limit</source>
        <translation>Karte eingrenzen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="325"/>
        <source>geometrymode</source>
        <translation>Geometriemodus</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="194"/>
        <source>pixel</source>
        <translation>Pixel</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="174"/>
        <location filename="../mainwindow.ui" line="1904"/>
        <source>block</source>
        <translation>Kartenblock (16x16x16)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="311"/>
        <source>fixed</source>
        <translation>Fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="230"/>
        <source>shrink</source>
        <translation>verkleinern</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="362"/>
        <source>Heightmap</source>
        <translation>Höhenkarte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="817"/>
        <source>Specify the nodes list for the height map</source>
        <translation>Legt die Liste für Höhenkarten-nodes fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="900"/>
        <location filename="../mainwindow.ui" line="920"/>
        <source>Specify the color definition file for the height map</source>
        <translation>Legt die Farbdefinitionsliste für die Höhenkarte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="873"/>
        <source>a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation type="unfinished">Eine Monochrome Karte wird erstellt. </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="879"/>
        <source>e.g. grey,black, #00FF00</source>
        <translation>z.B. grey, black, #00FF00</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="847"/>
        <source>If a color is given, a monochrome map is generated in shades of that color, ranging from black at depth -128 to the given color at height 127.</source>
        <translation>Wenn eine Farbe festgelegt ist, wird eine Monochrome Karte in Schatten dieser farbe erstellt. Diese reicht von einer Tiefe von -128 bis 127.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="125"/>
        <source>Preview: </source>
        <translation>Vorschau: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="224"/>
        <source>Currently, shrinking is done with block granularity, and based on which blocks are in the database. As the database always contains a row or and column of empty, or partially empty blocks at the map edges, there will still be empty pixels at the edges of the map. Use --blockcolor to visualize these empty blocks.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="227"/>
        <source>Generate a map of at most the requested geometry. Shrink it to the smallest possible size that still includes the same information.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="168"/>
        <source>The requested geometry will be extended so that the map does not contain partial map blocks (of 16x16 nodes each). At least all pixels covered by the geometry will be in the map, but there may be up to 15 more in every direction.</source>
        <translation>Die gewählte Gometrie wird ausgedehnt, sodass die Karte nur ganze Kartenblöcke (16x16) einschließt. Alle Pixel der geometrie werden eingeschlossen, aber es können bis zu 15 Pixel mehr sein.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="171"/>
        <source>round the coodinates to a multiple of 16.</source>
        <translation>Rundet die Koordinaten auf ein vielfaches von 16.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="188"/>
        <source>A map of exactly the requested size is generated (after adjustments due to the &apos;shrink&apos; flag, or possible adjustments required by the scale factor).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="191"/>
        <source>interpret the coordinates with pixel granularity.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="181"/>
        <source>min-Y</source>
        <translation>Untere Höhengrenze</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="201"/>
        <location filename="../mainwindow.ui" line="338"/>
        <source>Specify the upper height limit for the map</source>
        <translation>Legt das Obere Höhenlimit für die Karte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="204"/>
        <source>max-Y</source>
        <translation>Obere Höhengrenze</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="335"/>
        <source>Nodes higher than this level will not be drawn. This can be used to avoid floating islands or floating artefacts from abscuring the world below.</source>
        <translation>Blöcke über diesem level werden nicht angezigt. Dies kann dazu verwendet werden um schwebende Inseln und andere gegenstände auszusortieren.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="240"/>
        <source>Any nodes below this level will not be drawn.</source>
        <translation>Alle Blöcke unterhalb dieses wertes werden nicht angezeigt.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="243"/>
        <source>Specify the lower height limit for the map</source>
        <translation>Legt das untere Höhenlimit für die Karte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="259"/>
        <source>e.g. -200,-100:200,200</source>
        <translation>z.B. -200,-100:200,200</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="305"/>
        <source>NOTE: If this flag is used, and no actual geometry is specified, this would result in a maximum-size map (65536 x 65536), which is currently not possible, and will fail, due to a bug in the drawing library.</source>
        <translation>&lt;b&gt;Achtung:&lt;/b&gt; Wenn dieser Parameter verwendet wird, ohne dass eine geometrie festgelegt ist wird eine Karte der Maximalen Größe (65536 x 65536) erstellt. Dies ist derzeit nicht möglich aufgrund eines fehlers der Zeichenbibliothek.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="308"/>
        <source>don&apos;t reduce the map size. What ever is specified using a geometry option, is what will be draw, even if partly or fully empty.</source>
        <translation>Kartengröße wird nicht reduziert. Alles was in der Geometrie festgelegt ist wird angezeigt, egal ob es leer ist.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="850"/>
        <source>Color</source>
        <translation>Farbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="857"/>
        <source>If no color is specified, minetestmapper will use a colors file to determine which colors to use at which height level.</source>
        <translation>Wenn keine Farbe festgelegt wurde, verwendet der minetestmapper eine datei.</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="860"/>
        <source>File</source>
        <translation>Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="933"/>
        <source>use color or select a heightmap-colors.txt file</source>
        <translation>Verwende eine Farbe, oder wähle eine heightmap-colors.txt datei aus</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="943"/>
        <source>heightmap Skale</source>
        <translation>Höhenkarte Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="949"/>
        <location filename="../mainwindow.ui" line="952"/>
        <source>Draw a height scale at the bottom of the map</source>
        <translation>Zeichne eine Höhenskala am unteren Rand der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="955"/>
        <source>Draw Heightscale</source>
        <translation>Zeichne Höhenkartenskala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="995"/>
        <source>other</source>
        <translation>Weitere</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1001"/>
        <source>Y-scale</source>
        <translation>Y-Skalierung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1021"/>
        <source>Height level 0</source>
        <translation>Normal Null höhe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1059"/>
        <source>Colors</source>
        <translation>Farben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1065"/>
        <source>tilebordercolor</source>
        <translation>Rasterfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1072"/>
        <source>Specify the background color for the image</source>
        <translation>Legt die Hintergrundfarbe für das Bild fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1085"/>
        <source>bgcolor</source>
        <translation>Hintergrundfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1099"/>
        <source>playercolor</source>
        <translation>Spielerfarbe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1106"/>
        <source>Specify the color for empty mapblocks</source>
        <translation>Legt die Farbe für leere kartenabschnitte fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1116"/>
        <source>blockcolor</source>
        <translation>Farbe für leere Kartenabschnitte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1123"/>
        <source>origincolor</source>
        <translation>Farbe des Ursprungs</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1130"/>
        <source>scalecolor</source>
        <translation>Farbe der Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1234"/>
        <source>Specify the color for drawing tile borders</source>
        <translation>Legt die Farbe des Rasters fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1244"/>
        <source>Specify the color for drawing player locations</source>
        <translation>Legt die Farbe der Spielerpositionen fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1254"/>
        <source> Specify the color for drawing the map origin (0,0)</source>
        <translation>Legt die Farbe der Ursprungsmarkierung fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1264"/>
        <source> Specify the color for text in the scales on the side</source>
        <translation>Legt die Farbe des Textes in der Skala fest</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1275"/>
        <source>Map features</source>
        <translation>Eigenschaften</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1338"/>
        <source>Draw origin</source>
        <translation>zeichne Ursprung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1281"/>
        <source>Draw a scale on the left and/or top edge</source>
        <translation>Zeichnet eine Skala links und/oder oben auf der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1284"/>
        <source>drawscale</source>
        <translation>Zeichne Skala</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2350"/>
        <source>edit colors.txt</source>
        <translation>bearbeite colors.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2358"/>
        <source>edit heightmap-nodes.txt</source>
        <translation>bearbeite heightmap-nodes.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2366"/>
        <source>edit heightmap-colors.txt</source>
        <translation>bearbeite heightmap-colors.txt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1335"/>
        <source> Draw a circle at the origin (0,0) on the map</source>
        <translation>Zeichne ein Kreis am Mittelpunkt (0,0) auf der Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1362"/>
        <source>Enable drawing transparency for some nodes (e.g. water)</source>
        <translation>Zeichnet Transparenz z.B. für Wasser</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1345"/>
        <source>Draw circles at player positions on the map</source>
        <translation>Zeichet kreise bei den Spielerpositionen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1348"/>
        <source>Draw Players</source>
        <translation>Zeichne Spielerpossitionen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1392"/>
        <source>Draw air nodes (read the warnings first!)</source>
        <translation>Macht Luft sichtbar (bitte zuerst die Warnungen lesen)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1402"/>
        <source>Disable shading that accentuates height diffences</source>
        <translation>Deaktiviert die Schatten der Höhenunterschiede</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1298"/>
        <source>top</source>
        <translation>Oben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2143"/>
        <source>&amp;Edit</source>
        <translation>&amp;Bearbeiten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2172"/>
        <source>Main Toolbar</source>
        <translation>Hauptwerkzeugleiste</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2221"/>
        <source>qrc:/doc/intro.html</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2303"/>
        <source>Whats this?</source>
        <translation>Was ist das?</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2315"/>
        <source>Open World</source>
        <translation>Öffne Welt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2327"/>
        <source>Save map as</source>
        <translation>Speichere karte als</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1291"/>
        <source>left</source>
        <translation>Links</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1355"/>
        <source>Draw Alpha</source>
        <translation>Durchsichtiges Wasser</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1395"/>
        <source>Draw Air</source>
        <translation>Zeichne Luft</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1405"/>
        <source>No Shading</source>
        <translation>Keine Schatten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="368"/>
        <source>Generate a height map instead of a regular map</source>
        <translation>Erstellt eine Höhenkarte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="371"/>
        <source> Generate a height map instead of a regular map</source>
        <translation>Eine Höhenkarte anstatt einer normalen erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="811"/>
        <source>Heightmap nodes</source>
        <translation type="unfinished">Höhenkarte Nodes</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="66"/>
        <location filename="../mainwindow.ui" line="827"/>
        <location filename="../mainwindow.ui" line="903"/>
        <location filename="../mainwindow.ui" line="1223"/>
        <source>browse</source>
        <translation>Durchsuchen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="50"/>
        <source>Select the world directory, wich contains the world Database</source>
        <translation>Wählen Sie den Welt-ordner aus, der die Datenbank enthält</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="103"/>
        <location filename="../mainwindow.ui" line="132"/>
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
        <location filename="../mainwindow.ui" line="118"/>
        <source>map.png</source>
        <translation>karte.png</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="298"/>
        <source>scalefactor</source>
        <translation>Skalierfaktor</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="318"/>
        <source>geometry</source>
        <translation>Geometrie</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="351"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;geometry-syntax&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#0000ff;&quot;&gt;help&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="841"/>
        <source>Heightmap colors</source>
        <translation>Höhenkarte Farben</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="886"/>
        <location filename="../mainwindow.ui" line="1157"/>
        <location filename="../mainwindow.ui" line="1168"/>
        <location filename="../mainwindow.ui" line="1179"/>
        <location filename="../mainwindow.ui" line="1190"/>
        <location filename="../mainwindow.ui" line="1201"/>
        <location filename="../mainwindow.ui" line="1212"/>
        <location filename="../mainwindow.cpp" line="588"/>
        <location filename="../mainwindow.cpp" line="600"/>
        <location filename="../mainwindow.cpp" line="612"/>
        <location filename="../mainwindow.cpp" line="624"/>
        <location filename="../mainwindow.cpp" line="637"/>
        <location filename="../mainwindow.cpp" line="649"/>
        <location filename="../mainwindow.cpp" line="693"/>
        <source>select color</source>
        <translation>Farbe auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="965"/>
        <source>custom heightscale intervall</source>
        <translation>Benuzerdefinierte Höhenskalaeinteilung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="975"/>
        <location filename="../mainwindow.ui" line="1318"/>
        <source>Major: </source>
        <translation>Hauptskalierung: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="985"/>
        <location filename="../mainwindow.ui" line="1328"/>
        <source>Minor: </source>
        <translation>Nebenskalierung: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1137"/>
        <source>colors.txt file</source>
        <translation>colors.txt Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1308"/>
        <source>custom sidescale Interval</source>
        <translation>Benutzerdefinierte Skaleneinteilung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1413"/>
        <source>Tiles</source>
        <translation>Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1419"/>
        <source>Draw tiles</source>
        <translation>Zeichne Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1862"/>
        <source>tiles</source>
        <translation>Raster</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1871"/>
        <source>size: </source>
        <translation>Größe: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1890"/>
        <source>chunk</source>
        <translation>Kartengeneratorblock (5x5x5)</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1897"/>
        <source>tilesize+border</source>
        <translation>Größe+Rahmen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1917"/>
        <source>border: </source>
        <translation>Rahmen: </translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1933"/>
        <source>arrange</source>
        <translation>Ausrichten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1939"/>
        <source>tilecenter</source>
        <translation>Zentrieren</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1946"/>
        <source>tileorigin</source>
        <translation>Ursprung</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1956"/>
        <source>arrange at</source>
        <translation>Ausrichten an</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1962"/>
        <source>coordinates</source>
        <translation>Koordinaten</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1969"/>
        <source>world</source>
        <translation>Welt</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1979"/>
        <source>map</source>
        <translation>Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2042"/>
        <source>MinetestMapper Output</source>
        <translation>Ausgabe des minetestmapper</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2065"/>
        <source>select all</source>
        <translation>Alles auswählen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2072"/>
        <source>copy</source>
        <translation>In Zwischenablage kopiern</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2079"/>
        <source>clear</source>
        <translation>leeren</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2100"/>
        <source>Generate</source>
        <translation>Erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2114"/>
        <source>Cancel</source>
        <translation>Abbrechen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2133"/>
        <source>&amp;File</source>
        <translation>&amp;Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2152"/>
        <location filename="../mainwindow.ui" line="2197"/>
        <location filename="../mainwindow.ui" line="2295"/>
        <source>Help</source>
        <translation>Hilfe</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2162"/>
        <source>Language</source>
        <translation>Sprache</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2240"/>
        <location filename="../mainwindow.cpp" line="674"/>
        <source>About MinetestMapper</source>
        <translation>Über MinetestMapper</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2251"/>
        <source>About QT</source>
        <translation>Über QT</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2266"/>
        <source>generate Map</source>
        <translation>Karte Erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2269"/>
        <source>starting Minetestmapper to generate the map</source>
        <translation>startet den Minetestmapper um die Karte zu erstellen</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2272"/>
        <source>generate the Map</source>
        <translation>erstellt die Karte</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2280"/>
        <source>Exit</source>
        <translation>Beenden</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="105"/>
        <source>Current Language changed to %1</source>
        <translation>Sprache wurde auf %1 geändert</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="2339"/>
        <location filename="../mainwindow.cpp" line="660"/>
        <source>About MinetestMapper GUI</source>
        <translation>Über MinetestMapperGUI</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="139"/>
        <source>no input world selected</source>
        <translation>Keine Minetestwelt ausgewählt</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="140"/>
        <source>ERROR: No MinetestWorld selected&lt;br&gt;&lt;br&gt;please select a world</source>
        <translation>FEHLER: Keine Minetestwelt ausgewählt&lt;br&gt;&lt;br&gt;Bitte wähle eine Welt aus</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="146"/>
        <source>the Image File does already exist</source>
        <translation>Das Bild existiert bereits</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="147"/>
        <source>The File &lt;i&gt;%1&lt;/i&gt; does already exist. &lt;br&gt;&lt;br&gt;Do you want to overwrite?</source>
        <translation>Die Datei &lt;i&gt;%1&lt;/i&gt; existiert bereits. &lt;br&gt;&lt;br&gt;Soll die Datei Überschrieben werden?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="156"/>
        <source>the directory does not exist</source>
        <translation>Der Ordner existiert nicht</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="157"/>
        <source>The directory &lt;i&gt;%1&lt;/i&gt; does not exist. &lt;br&gt;&lt;br&gt;Should it be created?</source>
        <translation>Der Ordner &lt;i&gt;%1&lt;/i&gt; existiert nicht. &lt;br&gt;&lt;br&gt;Möchten sie den Ordner erstellen?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="380"/>
        <source>Finisched :)</source>
        <translation>Fertig :-)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="385"/>
        <source>minetestmapper terminated</source>
        <translation>minetestmapper abgebrochen</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="388"/>
        <location filename="../mainwindow.cpp" line="403"/>
        <source>Minetest Mapper failed</source>
        <translation>Minetestmapper hat ein Fehler festgestellt</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="389"/>
        <source>&lt;h1&gt;ERROR&lt;/h1&gt; &lt;h2&gt;minetestmapper failed&lt;/h2&gt;Exit code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Status of MinetestMapper: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;&lt;br&gt;Please fix the error and try again </source>
        <translation>&lt;h1&gt;Fehler&lt;/h1&gt; &lt;h2&gt;kartenerstellung fehlgeschlagen&lt;/h2&gt;Exit code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Ausgabe des Minetstmapper: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;&lt;br&gt;Bitte den Fehler beheben und erneut versuchen </translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="404"/>
        <source>&lt;h1&gt;ERROR&lt;/h1&gt; &lt;h2&gt;minetestmapper failed&lt;/h2&gt;Error code: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Error Message: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;</source>
        <translation type="unfinished">&lt;h1&gt;FEHLER&lt;/h1&gt; &lt;h2&gt;minetestmapper ist abgestürzt&lt;/h2&gt;Fehlercode: &lt;i&gt;%1&lt;/i&gt; &lt;br&gt;Fehlernachricht: &lt;pre&gt;%2&lt;/pre&gt;&lt;br&gt;</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="546"/>
        <source>Open Minetest World</source>
        <translation>Minetest Welt-Ordner öffnen</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="556"/>
        <source>Save generated map to...</source>
        <translation>Karte speichern nach...</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="556"/>
        <source>png image (*.png)</source>
        <translation>png Grafik (*.png)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="563"/>
        <source>Open HeightmapNodes File</source>
        <translation>Öffne HeightmapNodes Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="565"/>
        <location filename="../mainwindow.cpp" line="573"/>
        <location filename="../mainwindow.cpp" line="581"/>
        <source>TXT File (*.txt)</source>
        <translation>TXT Datei (*.txt)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="571"/>
        <source>Open HeightmapColors File</source>
        <translation>Öffne Höhenkarte Farbdefinitionsdatei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="579"/>
        <source>Open colors.txt File</source>
        <translation>Öffne colors.txt Datei</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="661"/>
        <source>&lt;h1&gt;About MinetestMapperGUI&lt;/h1&gt;The &lt;b&gt;MinetestMapper Gui&lt;/b&gt; is written by addi.&lt;br /&gt;It is licensed under a &lt;a href=&quot;http://creativecommons.org/licenses/by/3.0/&quot;&gt;Creative Commons Attribution 3.0 Unported License&lt;/a&gt;.&lt;br&gt;The current version is %1.%2.%3. &lt;br&gt;The sourcecode is aviable on &lt;a href=&apos;https://bitbucket.org/adrido/minetestmappergui/&apos;&gt;Bitbucket&lt;/a&gt;&lt;br&gt;You may also want to read the &lt;a href=&apos;https://forum.minetest.net/viewtopic.php?f=14&amp;t=12139&apos;&gt;Minetest forum thread&lt;/a&gt;&lt;br&gt;&lt;br&gt;&lt;b&gt;Thanks to:&lt;/b&gt;&lt;br&gt;McKrustenkaese for his great icon</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="675"/>
        <source>&lt;h1&gt;About MinetestMapper&lt;/h1&gt;The &lt;b&gt;MinetestMapper&lt;/b&gt; is written by:&lt;br&gt;Miroslav Bendík &lt;miroslav.bendik@gmail.com&gt;&lt;br&gt;ShadowNinja &lt;shadowninja@minetest.net&gt;&lt;br&gt;sfan5 &lt;sfan5@live.de&gt;&lt;br&gt;Rogier &lt;rogier777@gmail.com&gt;&lt;br&gt;&lt;br&gt;&lt;u&gt;License:&lt;/u&gt;LGPLv2.1+ and BSD 2-clause.&lt;br&gt;Source Code: &lt;a href=&apos;https://github.com/Rogier-5/minetest-mapper-cpp&apos;&gt;Github&lt;/a&gt;&lt;br&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="687"/>
        <source>preview: %1</source>
        <translation>Vorschau: %1</translation>
    </message>
</context>
</TS>
