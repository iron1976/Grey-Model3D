# Grey-Model3D
This is a 3D Model Editor. You can either import or export .obj files using this 3D Model Editor.
<h1>Components</h1>
<h2>Transform</h2>
This component is a must otherwise nothing will be rendered.
<br></br>
You can control the position and the size of the object.
<br></br>
Variables:
SizX: Width of the object, default: 1
<br></br>
SizY: Height of the object, default: 1
<br></br>
SizZ: Z Size(not thiccness) of the object, default: 1
<br></br>
Pos0: Position of the object, default: (0.0,0.0,0.0)
<br></br>
<h2>Mesh</h2>
This component contains the points and colors of the object.
Variables: 
ColR: Red of color, default: 1
<br></br>
ColG: Red of green, default: 1
ColB: Red of blue, default: 1
<br></br>
ColA: Alpha of color, default: 1
<br></br>
Ver∞: Point
<br></br>
<h2>Texture</h2>
Path: full path of texture
<br></br>
SizX: Width of the texture if this var is negative texture will be inverted horizontally, default: 1
<br></br>
SizY: Height of the texture if this var is negative texture will be inverted vertically, default: 1
<br></br>
<h2>Mirror</h2>
Variables: 
IDs: ID(s) of objects that will be reflected on mirror ex: IDs:6,1 object with id 6 and 1 will be reflected.
<br></br>
SizX: Width of the reflection if this var is negative reflection will be inverted horizontally, default: 2
<br></br>
SizY: Height of the reflection if this var is negative reflection will be inverted vertically, default: 2
<br></br>
