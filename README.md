Test 1 
https://youtu.be/-m56RPWUfJk?si=SDYONJksNOHRVL-6

Test 2 
https://youtu.be/GynMSmLK3CA?si=HyWtIWURXR0BS3CE


# BitClicks

<table>
  <thead style="color:#00FF00; background:#000000;">
    <tr>
      <th>Feature</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody style="color:#00FF00; background:#000000;">
    <tr>
      <td>Clicker Mechanics</td>
      <td>Increment bits by clicking and buy upgrades to increase bits per click.</td>
    </tr>
    <tr>
      <td>Rebirth System</td>
      <td>Reset progress with multipliers for faster growth.</td>
    </tr>
    <tr>
      <td>3D Mode</td>
      <td>Toggle between 2D clicker and simple 3D isometric view.</td>
    </tr>
    <tr>
      <td>Custom UI</td>
      <td>Boot animation, upgrade menu, and number input popup.</td>
    </tr>
  </tbody>
</table>

---

<p align="center">
  <img src="https://readme-typing-svg.demolab.com/?lines=BitClicks&font=Fira+Code&center=true&width=600&height=45&color=800080&pause=0&speed=50&size=26&vCenter=true" alt="BitClicks" />
</p>


<p align="center" style="color:#00FF00; font-family:'Fira Code', monospace; font-size:18px;">
  Pure C | raylib-based | Minimal external dependencies | <strong>Linux Only</strong>
</p>

---

## About

BitClicks is a work-in-progress C project featuring a simple clicker game combined with a 3D isometric demo OS interface.  
Built with [raylib](https://www.raylib.com/), it demonstrates:  
- Incremental upgrades  
- Rebirth mechanics for progression  
- A basic 3D camera and movement  
- Custom particle and boot animations  

---

## Platform Support

⚠️ <strong>Currently designed and tested on Linux only.</strong>  
Dependencies and build instructions target Linux environments (X11, pthread, OpenGL).  
Windows or macOS support may require adjustments.

---

## How to Build

Ensure you have raylib installed on your Linux system.

Compile with:

```bash
gcc main.c ig.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o BitClicks
