import React from 'react';

const ScoreBoard = ({ score, currentTurn, player1, player2 }) => {
  return (
    <div className="bg-white p-4 rounded-lg shadow-md mb-4">
      <div className="grid grid-cols-3 gap-4 text-center">
        <div className={`p-2 rounded ${currentTurn === 1 ? 'bg-red-100' : ''}`}>
          <div className="font-bold text-red-500">{player1}</div>
          <div className="text-2xl">{score.player1}</div>
        </div>
        <div className="p-2">
          <div className="font-bold text-gray-500">Ties</div>
          <div className="text-2xl">{score.tie}</div>
        </div>
        <div className={`p-2 rounded ${currentTurn === 2 ? 'bg-blue-100' : ''}`}>
          <div className="font-bold text-blue-500">{player2}</div>
          <div className="text-2xl">{score.player2}</div>
        </div>
      </div>
    </div>
  );
};

export default ScoreBoard;