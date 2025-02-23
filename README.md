# Grey-Model3D
https://www.youtube.com/watch?v=ULxS7v6Lmf8
<a href="https://www.youtube.com/watch?v=ULxS7v6Lmf8">
  <img src="https://img.youtube.com/vi/ULxS7v6Lmf8/hqdefault.jpg" width="400">
</a> 


This is a 3D Model Editor. You can either import or export .obj files using this 3D Model Editor.
<h1>Components</h1>
<h2>Transform</h2>
This component is a must otherwise nothing will be rendered.<br>
You can control the position and the size of the object.<br>
Variables:<br>
SizX: Width of the object, default: 1<br>
SizY: Height of the object, default: 1<br>
SizZ: Z Size(not thiccness) of the object, default: 1<br>
Pos0: Position of the object, default: (0.0,0.0,0.0)<br>
<h2>Mesh</h2>
This component contains the points and colors of the object.<br>
Variables:<br>
ColR: Red of color, default: 1<br>
ColG: Red of green, default: 1<br>
ColB: Red of blue, default: 1<br>
ColA: Alpha of color, default: 1<br>
Ver∞: Point<br>
<h2>Texture</h2>
Component to set Texture to a mesh. (Requires Mesh Component)<br>
Variables:<br>
Path: full path of texture<br>
SizX: Width of the texture if this var is negative texture will be inverted horizontally, default: 1<br>
SizY: Height of the texture if this var is negative texture will be inverted vertically, default: 1<br>
<h2>Mirror</h2>
Component to set object reflect. (Requires Mesh Component)<br>
Variables:<br>
IDs: ID(s) of objects that will be reflected on mirror ex: IDs:6,1 object with id 6 and 1 will be reflected.<br>
SizX: Width of the reflection if this var is negative reflection will be inverted horizontally, default: 2<br>
SizY: Height of the reflection if this var is negative reflection will be inverted vertically, default: 2<br>
<br>
<h1>How-To?</h1>
<h2>Export .obj file</h2>
Click to your object and click on Save Object option write your path to export and click on Save That's it!
<img src="https://cdn.discordapp.com/attachments/711524717743308821/935146135587266560/unknown.png">
<img src="https://cdn.discordapp.com/attachments/711524717743308821/935146238825865276/unknown.png">
<br>
<h2>Import .obj file</h2>
Go to inspector click to the plus option write your path click on Add Object option That's it!
<img src="https://cdn.discordapp.com/attachments/711524717743308821/935146401074147398/unknown.png">
<img src="https://cdn.discordapp.com/attachments/711524717743308821/935146447790301254/unknown.png">

Note: While importing .obj files only mesh data will be imported.
