import Player from "./components/Player";
import GameBoard from "./components/GameBoard";
import { useState } from "react";
import Log from "./components/Log";
import GameOver from "./components/GameOver";
import {WINNING_COMBINATIONS} from "./winning-combinations";


const INITIAL_BOARD_GAME = [
  [null,null,null],
  [null,null,null],
  [null,null,null],
];

const PLAYERS =  {
  X: "player1", 
  O: "player2"
};

function deriveActivePlayer(gameTurns){
  let currentPlayer = 'X';

  if(gameTurns.length > 0 && gameTurns[0].player === 'X')
    currentPlayer = 'O';
  return currentPlayer;
}

function deriveBoardGame(gameTurns){
  let gameBoard = [...INITIAL_BOARD_GAME.map((innerArray) => [...innerArray] )];
  for (const turn of gameTurns){
      const {squre, player} = turn;
      const {row, col} = squre;
      gameBoard[row][col] = player;
  }
  return gameBoard;
}

function deriveWinner(players, gameBoard){
  let winner;
  for(const comb of WINNING_COMBINATIONS){
    const firstSymbol = gameBoard[comb[0].row][comb[0].column];
    const secondSymbol = gameBoard[comb[1].row][comb[1].column];
    const thirdSymbol = gameBoard[comb[2].row][comb[2].column];

    if (firstSymbol && (firstSymbol === secondSymbol) && (firstSymbol === thirdSymbol)){
      winner = players[firstSymbol];
    }
  }
  return winner;
}

function App() {
  
  const [players, setPlayers] = useState(PLAYERS);
  const [gameTurns, setGameTurns] = useState([]);

  const activePlayer = deriveActivePlayer(gameTurns);
  const gameBoard = deriveBoardGame(gameTurns);
  const winner = deriveWinner(players, gameBoard);
  
  const hasDraw = gameTurns.length === 9 && !winner;
    
  function handlePlayerNameChanged(symbol, newName){
    setPlayers((prevPlayers) => {
      return {
        ...prevPlayers,
        [symbol]: newName
      };
    })
  }

  function handleClickSqure(rowIndex, colIndex){
    setGameTurns((prevTurns)=> {
      const currentPlayer = deriveActivePlayer(prevTurns);
      const udpatedTurns = [{squre: {row: rowIndex, col: colIndex}, player: currentPlayer } ,...prevTurns];
      return udpatedTurns;
    })
  }

  function handleRestart(){
    setGameTurns([]);
  }

  return (
    <main>
      <div id = "game-container">
        <ol id="players" className="highlight-player">      
          <Player 
            onChangedName = {handlePlayerNameChanged} 
            initialName = {PLAYERS.X} 
            symbol = "X" 
            isActive={activePlayer === 'X'}
          />
          <Player 
            onChangedName = {handlePlayerNameChanged} 
            initialName= {PLAYERS.O} 
            symbol = "O" 
            isActive={activePlayer === 'O'}
          />
        </ol>
        {(winner || hasDraw) && <GameOver onRestart = {handleRestart} winner = {winner}/> }
        <GameBoard onSelectedSqure = {handleClickSqure} board = {gameBoard}/>
      </div>
      <Log turns = {gameTurns}/>
    </main>
  );
}

export default App
