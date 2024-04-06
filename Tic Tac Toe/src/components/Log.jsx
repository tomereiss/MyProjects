export default function Log({turns}){
    let logList = [];
    for (const turn of turns){
        const {squre, player} = turn;
        const {row, col} = squre;
        logList.push(`${player} selected ${row}, ${col}`);
    }
    return (
        <ol id="log">
            {logList.map((logMessage, index) => (
                <li key = {index}>
                   {logMessage}
                </li>
            ))}
        </ol>
    );
}



