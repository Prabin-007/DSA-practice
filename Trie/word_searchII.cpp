//  bhai naya cheez jaane ko mila bass ek dir se &dir karne mai code fail se work karne laga , analyze kyu

// That single & is one of the most famous performance traps in C++.

// When you wrote for(auto dir : directions), you were passing by value. This means C++ was dynamically allocating memory and creating a brand-new copy of your vector<int> for every single direction checked.

// In a DFS exploring a grid, you might make hundreds of thousands of recursive calls. Without the &, you were forcing the computer to create, copy, and destroy hundreds of thousands of temporary vectors in a fraction of a second. Memory allocation is incredibly slow compared to basic logic.

// By changing it to for(auto& dir : directions), you changed it to pass by reference:

// C++ immediately stopped copying.

// Instead of building new vectors, it just looked at the exact memory address of your existing directions array.

// You eliminated massive overhead instantly, allowing the DFS to run at full speed.