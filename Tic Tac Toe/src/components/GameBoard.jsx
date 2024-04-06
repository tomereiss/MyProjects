// import {WINNING_COMBINATIONS} from "../winning-combinations";

// const initialBoardGame = [
//     [null,null,null],
//     [null,null,null],
//     [null,null,null],
//   ];

export default function GameBoard({onSelectedSqure, board}){

    // let board = initialBoardGame;
    // for (const turn of turns){
    //     const {squre, player} = turn;
    //     const {row, col} = squre;
    //     board[row][col] = player;
    // }

    return(
        <ol id="game-board">
            {board.map((row, rowIndex) => ( 
                <li key = {rowIndex}>
                    <ol>
                        {row.map((playerSymbol, colIndex) => (
                            <li key = {colIndex}>
                                <button 
                                onClick={() => onSelectedSqure(rowIndex, colIndex)} 
                                disabled={playerSymbol !== null}
                                >
                                    {playerSymbol}
                                </button>
                            </li>
                        ))}
                    </ol>
                </li> 
            ))}  
        </ol>
    );
}