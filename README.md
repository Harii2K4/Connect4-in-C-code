Connect4 Game

This project is a full-stack implementation of the classic Connect4 game. The frontend is built using React.js, while the backend is written in C. TailwindCSS is used for styling.

Features

Interactive Gameplay: Play Connect4 with an intuitive and responsive UI.

Real-time Updates: The game state updates dynamically as players take turns.

Backend in C: The backend logic for the game is implemented in C for optimized performance.

Modern UI: Built with React.js and styled using TailwindCSS.

Technologies Used

Frontend: React.js, TailwindCSS

Backend: C

Installation

Prerequisites

Make sure you have the following installed on your system:

Node.js

gcc (C Compiler)

Clone the Repository

git clone https://github.com/yourusername/connect4.git
cd connect4

Setup Backend

Compile the C code:

gcc -o connect4_backend connect4.c

Start the backend server:

./connect4_backend

Setup Frontend

Install dependencies:

npm install

Start the development server:

npm start

Usage

Open your browser and navigate to http://localhost:3000.

Start playing Connect4 with another player.

Project Structure

connect4/
├── src/
├── connect4_backend (compiled backend binary)
├── connect4.c (backend source file)
├── package.json
├── package-lock.json
├── postcss.config.js
├── tailwind.config.js
├── README.md
└── .gitignore

Contributing

Contributions are welcome! Please follow these steps:

Fork the repository.

Create a new branch for your feature or bug fix.

Commit your changes and push to your branch.

Submit a pull request.

License

This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments

Thanks to the contributors of React.js, gcc, and TailwindCSS for providing the tools to build this project.

Inspired by the classic Connect4 game.
