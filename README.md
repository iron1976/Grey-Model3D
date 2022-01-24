# Grey-Model3D
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
<br>
<h2>Export .obj file</h2>
![image](https://user-images.githubusercontent.com/60754890/150787003-aae80885-39d7-4aa6-8831-56d2534e560c.png)
