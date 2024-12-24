import React from 'react';

const Cell = ({ value }) => {
  const getCellColor = () => {
    if (value === 1) return 'bg-red-500';
    if (value === 2) return 'bg-blue-500';
    return 'bg-gray-200';
  };

  return (
    <div className="w-12 h-12 border border-gray-300 rounded-full m-1">
      <div className={`w-full h-full rounded-full ${getCellColor()} transition-colors duration-300`}></div>
    </div>
  );
};

export default Cell;