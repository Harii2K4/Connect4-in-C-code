import React from 'react';
import Cell from './Cell';

const Board = ({ board, onColumnClick }) => {
  return (
    <div className="bg-blue-100 p-4 rounded-lg">
      <div className="grid grid-cols-9 gap-1">
        {Array.from({ length: 9 }).map((_, col) => (
          <button
            key={col}
            className="hover:bg-blue-200 p-2 rounded-t-lg transition-colors"
            onClick={() => onColumnClick(col + 1)}
          >
            ↓
          </button>
        ))}
      </div>
      <div className="bg-blue-300 p-4 rounded-lg">
        {board.map((row, rowIndex) => (
          <div key={rowIndex} className="flex justify-center">
            {row.map((cell, colIndex) => (
              <Cell key={`${rowIndex}-${colIndex}`} value={cell} />
            ))}
          </div>
        ))}
      </div>
    </div>
  );
};

export default Board;