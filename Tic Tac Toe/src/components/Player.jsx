import { useState } from "react";

export default function Player({initialName, symbol, isActive, onChangedName}){
    const [isEditing, setIsEditing] = useState(false);
    const [playerName, setPlayerName] = useState(initialName);
    function handleEditClick(){
        //setIsEditing(!isEditing); => Dangerous way. React schedules the performance of the function, so be based on the last previous value like that is not recommended
        setIsEditing((editing) => !editing); // a better way to ensure that when the function is being performed, the value of "editing" is updated
        if(isEditing)
            onChangedName(symbol, playerName);
    }
    function handleChangeName(event){
        console.log(event);
        setPlayerName(event.target.value);
    }
    return (
        <li className={isActive ? 'active' : undefined}>
            <span className="player">
                {isEditing?  <input type="text" required value={playerName} onChange = {handleChangeName}/>
                    :<span className="player-name">{playerName}</span>}
                <span className="player-symbol">{symbol}</span>
            </span>
            <button onClick={handleEditClick}>{isEditing? 'Save' : 'Edit'}</button>
        </li>
    );
}