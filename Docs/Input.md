# Input Library

## Global Functions
<details><summary>Button</summary>

```cpp
bool Button(const std::string& name);                           // Normal variant
bool Button(Binding button);                                    // Direct binding variant
bool Button(const std::string& group, const std::string& name); // Group variant
```
  
Thread Safe: **NO**.  
Checks if the `ButtonBinding` depicted by '**name**' or the direct binding '**button**' is currently held down. If '**group**' is speicified, it checks the `ButtonBinding` in that input group.  
Returns `true` if the button is down.
  
</details>
<details><summary>ButtonState</summary>

```cpp
std::uint8_t ButtonState(const std::string& name);                           // Normal variant
std::uint8_t ButtonState(Binding button);                                    // Direct binding variant
std::uint8_t ButtonState(const std::string& group, const std::string& name); // Group variant
```
  
Thread Safe: **NO**.  
Gets the state of the `ButtonBinding` depicted by '**name**' or the direct binding '**button**'. If '**group**' is specified, it gets it from the `ButtonBinding` in that input group.  
Returns a bitfield following:
| Bit | Description |
| :---: | --- |
| 0 | Is the button pressed |
| 1 | Is the button repeated |
| 2 | Is the button released |
| 2 | Is the button down |
  
</details>
<details><summary>ButtonPressed</summary>

```cpp
bool ButtonPressed(const std::string& name);                           // Normal variant
bool ButtonPressed(Binding button);                                    // Direct binding variant
bool ButtonPressed(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Checks if the `ButtonBinding` depicted by '**name**' or the direct binding '**button**' is currently pressed. If '**group**' is speicified, it checks the `ButtonBinding` in that input group.  
Returns `true` if the button is pressed.

</details>
<details><summary>ButtonRepeated</summary>

```cpp
bool ButtonRepeated(const std::string& name);                           // Normal variant
bool ButtonRepeated(Binding button);                                    // Direct binding variant
bool ButtonRepeated(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Checks if the `ButtonBinding` depicted by '**name**' or the direct binding '**button**' is currently repeated. If '**group**' is speicified, it checks the `ButtonBinding` in that input group.  
Returns `true` if the button is repeated.

</details>
<details><summary>ButtonReleased</summary>

```cpp
bool ButtonReleased(const std::string& name);                           // Normal variant
bool ButtonReleased(Binding button);                                    // Direct binding variant
bool ButtonReleased(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Checks if the `ButtonBinding` depicted by '**name**' or the direct binding '**button**' is currently released. If '**group**' is speicified, it checks the `ButtonBinding` in that input group.  
Returns `true` if the button is released.

</details>

<details><summary>Axis</summary>

```cpp
float Axis(const std::string& name);                           // Normal variant
float Axis(Binding axis);                                      // Direct binding variant
float Axis(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Gets the state of the `AxisBinding`/`ButtonAxisBinding` depicted by '**name**' or the direct binding '**axis**'. If '**group**' is specified, it gets it from the `AxisBinding`/`ButtonAxisBinding` in that input group.  

</details>
<details><summary>Axis2D</summary>

```cpp
glm::fvec2 Axis2D(const std::string& name);                           // Normal variant
glm::fvec2 Axis2D(Binding xAxis, Binding yAxis);                      // Direct binding variant
glm::fvec2 Axis2D(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Gets the state of the `Axis2DBinding`/`ButtonAxis2DBinding` depicted by '**name**' or the 2D vector comprising the direct bindings '**xAxis**' and '**yAxis**'. If '**group**' is specified, it gets it from the `Axis2DBinding`/`ButtonAxis2DBinding` in that input group.  

</details>
<details><summary>Axis3D</summary>

```cpp
glm::fvec3 Axis3D(const std::string& name);                           // Normal variant
glm::fvec3 Axis3D(Binding xAxis, Binding yAxis, Binding zAxis);       // Direct binding variant
glm::fvec3 Axis3D(const std::string& group, const std::string& name); // Group variant
```

Thread Safe: **NO**.  
Gets the state of the `Axis3DBinding`/`ButtonAxis3DBinding` depicted by '**name**' or the 3D vector comprising the direct bindings '**xAxis**', '**yAxis**' and '**zAxis**'. If '**group**' is specified, it gets it from the `Axis3DBinding`/`ButtonAxis3DBinding` in that input group.  

</details>



<details><summary>GetGroup</summary>
  
```cpp
InputGroup* GetGroup(const std::string& name);
```
  
Thread Safe: **NO**.  
Gets an input group depicted by '**name**'.  
Returns `nullptr` when the input group doesn't exist, otherwise a valid pointer to an input group.
  
</details>
<details><summary>CreateGroup</summary>

```cpp
InputGroup* CreateGroup(const std::string& name); // Copy variant
InputGroup* CreateGroup(std::string&& name);      // Move variant
```

Thread Safe: **NO**.  
Creates an input group with the name '**name**'.  
Returns `nullptr` when a group with that name already exists, otherwise a valid pointer to the newly creaed input group.

  
</details>
<details><summary>GetOrCreateGroup</summary>

```cpp
InputGroup* GetOrCreateGroup(const std::string& name); // Copy variant
InputGroup* GetOrCreateGroup(std::string&& name);      // Move variant
```
  
Thread Safe: **NO**.  
Tries to get an input group depicted by '**name**', if one was found returns that, otherwise creates a new input group with the name '**name**'.  
Returns `nullptr` in the event of a critical bug, otherwise a valid pointer to an input group that already existed or a newly created input group.
  
</details>
<details><summary>EnableGroup</summary>

```cpp
void EnableGroup(const std::string& name);
```
  
Thread Safe: **NO**.  
Enables the input group depicted by '**name**'.
  
</details>
<details><summary>DisableGroup</summary>

```cpp
void DisableGroup(const std::string& name);
```
  
Thread Safe: **NO**.  
Disables the input group depicted by '**name**'.
  
</details>
<details><summary>ToggleGroup</summary>

```cpp
void ToggleGroup(const std::string& name);
```
  
Thread Safe: **NO**.  
Toggles the input group depicted by '**name**'.
  
</details>
<details><summary>IsGroupEnabled</summary>

```cpp
bool IsGroupEnabled(const std::string& name);
```
  
Thread Safe: **NO**.  
Returns `true` if the input group depicted by '**name**' is enabled.
  
</details>



<details><summary>RegisterButtonBinding</summary>

```cpp
void RegisterButtonBinding(const std::string& name, std::uint32_t button, EInputLocation location, std::uint32_t id);                           // Copy variant
void RegisterButtonBinding(std::string&& name, std::uint32_t button, EInputLocation location, std::uint32_t id);                                // Move variant
void RegisterButtonBinding(const std::string& group, const std::string& name, std::uint32_t button, EInputLocation location, std::uint32_t id); // Group copy variant
void RegisterButtonBinding(const std::string& group, std::string&& name, std::uint32_t button, EInputLocation location, std::uint32_t id);      // Group move variant
void RegisterButtonBinding(const std::string& name, Binding button);                                                                            // Direct binding copy variant
void RegisterButtonBinding(std::string&& name, Binding button);                                                                                 // Direct binding move variant
void RegisterButtonBinding(const std::string& group, const std::string& name, Binding button);                                                  // Group direct binding copy variant
void RegisterButtonBinding(const std::string& group, std::string&& name, Binding button);                                                       // Group direct binding move variant
```

Thread Safe: **NO**.  
Registers a `ButtonBinding` to the '**button**' at '**location**' of '**id**' or the direct binding '**button**' with the name '**name**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterAxisBinding</summary>

```cpp
void RegisterAxisBinding(const std::string& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id);                           // Copy variant
void RegisterAxisBinding(std::string&& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id);                                // Move variant
void RegisterAxisBinding(const std::string& group, const std::string& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id); // Group copy variant
void RegisterAxisBinding(const std::string& group, std::string&& name, std::uint32_t axis, float sensitivity, EAxisMode mode, EInputLocation location, std::uint32_t id);      // Group move variant
void RegisterAxisBinding(const std::string& name, Binding axis, EAxisMode mode);                                                                                               // Direct binding copy variant
void RegisterAxisBinding(std::string&& name, Binding axis, EAxisMode mode);                                                                                                    // Direct binding move variant
void RegisterAxisBinding(const std::string& group, const std::string& name, Binding axis, EAxisMode mode);                                                                     // Group direct binding copy variant
void RegisterAxisBinding(const std::string& group, std::string&& name, Binding axis, EAxisMode mode);                                                                          // Group direct binding move variant
```

Thread Safe: **NO**.  
Registers an `AxisBinding` to the '**axis**' at '**location**' of '**id**' with '**sensitivity**' or the direct binding '**axis**' with the name '**name**' and '**mode**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterAxis2DBinding</summary>

```cpp
void RegisterAxis2DBinding(const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode);                           // Copy variant
void RegisterAxis2DBinding(std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode);                                // Move variant
void RegisterAxis2DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, EAxisMode mode); // Group copy variant
void RegisterAxis2DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, EAxisMode mode);      // Group move variant
```

Thread Safe: **NO**.  
Registers an `Axis2DBinding` to the '**xAxis**' and '**yAxis**' with the name '**name**' and '**mode**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterAxis3DBinding</summary>

```cpp
void RegisterAxis3DBinding(const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode);                           // Copy variant
void RegisterAxis3DBinding(std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode);                                // Move variant
void RegisterAxis3DBinding(const std::string& group, const std::string& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode); // Group copy variant
void RegisterAxis3DBinding(const std::string& group, std::string&& name, Binding xAxis, Binding yAxis, Binding zAxis, EAxisMode mode);      // Group move variant
```

Thread Safe: **NO**.  
Registers an `Axis3DBinding` to the '**xAxis**', '**yAxis**' and '**zAxis**' with the name '**name**' and '**mode**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterButtonAxisBinding</summary>

```cpp
void RegisterButtonAxisBinding(const std::string& name, Binding posButton, Binding negButton, EAxisMode mode);                           // Copy variant
void RegisterButtonAxisBinding(std::string&& name, Binding posButton, Binding negButton, EAxisMode mode);                                // Move variant
void RegisterButtonAxisBinding(const std::string& group, const std::string& name, Binding posButton, Binding negButton, EAxisMode mode); // Group copy variant
void RegisterButtonAxisBinding(const std::string& group, std::string&& name, Binding posButton, Binding negButton, EAxisMode mode);      // Group move variant
```

Thread Safe: **NO**.  
Registers an `ButtonAxisBinding` to the '**posButton**' and '**negButton**' with the name '**name**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterButtonAxis2DBinding</summary>

```cpp
void RegisterButtonAxis2DBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, EAxisMode mode);                           // Copy variant
void RegisterButtonAxis2DBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, EAxisMode mode);                                // Move variant
void RegisterButtonAxis2DBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, EAxisMode mode); // Group copy variant
void RegisterButtonAxis2DBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, EAxisMode mode);      // Group move variant
```

Thread Safe: **NO**.  
Registers an `ButtonAxis2DBinding` to the '**posXButton**', '**negXButton**', '**posYButton**' and '**negYButton**' with the name '**name**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterButtonAxis3DBinding</summary>

```cpp
void RegisterButtonAxis3DDBinding(const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton, EAxisMode mode);                           // Copy variant
void RegisterButtonAxis3DDBinding(std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton, EAxisMode mode);                                // Move variant
void RegisterButtonAxis3DDBinding(const std::string& group, const std::string& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton, EAxisMode mode); // Group copy variant
void RegisterButtonAxis3DDBinding(const std::string& group, std::string&& name, Binding posXButton, Binding negXButton, Binding posYButton, Binding negYButton, Binding posZButton, Binding negZButton, EAxisMode mode);      // Group move variant
```

Thread Safe: **NO**.  
Registers an `ButtonAxis2DBinding` to the '**posXButton**', '**negXButton**', '**posYButton**', '**negYButton**', '**posZButton**' and '**negZButton**' with the name '**name**'. If '**group**' is specified it binds to that input group.

</details>
<details><summary>RegisterBinding</summary>

```cpp
template <Bindable T> void RegisterBinding(const std::string& name, T&& binding);                           // Copy variant
template <Bindable T> void RegisterBinding(std::string&& name, T&& binding);                                // Move variant
template <Bindable T> void RegisterBinding(const std::string& group, const std::string& name, T&& binding); // Group copy variant
template <Bindable T> void RegisterBinding(const std::string& group, std::string&& name, T&& binding);      // Group move variant
```

Thread Safe: **NO**.  
Registers a bindable '**binding**' with the name '**name**'. If '**group**' is specified it binds to that input group.

</details>
