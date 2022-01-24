# Grey-Model3D
This is a 3D Model Editor. You can either import or export .obj files using this 3D Model Editor.
<h1>Components</h1>
<h2>Transform</h2>
This component is a must otherwise nothing will be rendered.
You can control the position and the size of the object.
Variables:
SizX: Width of the object, default: 1
SizY: Height of the object, default: 1
SizZ: Z Size(not thiccness) of the object, default: 1
Pos0: Position of the object, default: (0.0,0.0,0.0)
<h2>Mesh</h2>
This component contains the points and colors of the object.
Variables: 
ColR: Red of color, default: 1
ColG: Red of green, default: 1
ColB: Red of blue, default: 1
ColA: Alpha of color, default: 1
Ver∞: Point
<h2>Texture</h2>
Path: full path of texture
SizX: Width of the texture if this var is negative texture will be inverted horizontally, default: 1\n
SizY: Height of the texture if this var is negative texture will be inverted vertically, default: 1
<h2>Mirror</h2>
IDs: ID(s) of objects that will be reflected on mirror ex: IDs:6,1 object with id 6 and 1 will be reflected.
SizX: Width of the reflection if this var is negative reflection will be inverted horizontally, default: 2
SizY: Height of the reflection if this var is negative reflection will be inverted vertically, default: 2
