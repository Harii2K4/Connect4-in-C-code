import React, { useState } from 'react';
import Board from './components/Board';
import ScoreBoard from './components/ScoreBoard';
import GameControls from './components/GameControls';

const App = () => {
  const [gameState, setGameState] = useState(null);
  const [players, setPlayers] = useState({ player1: '', player2: '' });

  const startGame = async (gameConfig) => {
    try {
      const response = await fetch('http://localhost:8000/api/start', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(gameConfig),
      });
      const data = await response.json();
      if (data.success) {
        setGameState(data);
        setPlayers({
          player1: gameConfig.player1,
          player2: gameConfig.player2,
        });
      } else {
        console.error('Failed to start game:', data.error);
      }
    } catch (error) {
      console.error('Error starting game:', error);
    }
  };

  const makeMove = async (column) => {
    try {
      const response = await fetch('http://localhost:8000/api/move', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ column }),
      });
      const data = await response.json();
      if (data.success) {
        setGameState(data);
      } else {
        console.error('Failed to make move:', data.error);
      }
    } catch (error) {
      console.error('Error making move:', error);
    }
  };

  return (
    <div className="min-h-screen bg-gray-100 py-8">
      <div className="container mx-auto px-4">
        <h1 className="text-4xl font-bold text-center text-gray-800 mb-8">Connect Four</h1>
        {!gameState ? (
          <GameControls onStartGame={startGame} />
        ) : (
          <div className="max-w-3xl mx-auto">
            <ScoreBoard
              score={gameState.score}
              currentTurn={gameState.currentTurn}
              player1={players.player1}
              player2={players.player2}
            />
            <Board board={gameState.board} onColumnClick={makeMove} />
          </div>
        )}
      </div>
    </div>
  );
};

export default App;