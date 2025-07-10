// TODO 到時候新增顏色
// Started Making Date : 2025/7/1
// board[8- toCol][toRow - 'a'] (Important)
// [DEBUG]<Function (function name)>class:(class) , (Action)
// ===============std::cerr 的格式===============
#include <bits/stdc++.h>

using namespace std;
// 當一些不合法 或是成功該發的訊息
/*
============================================================================================
                                            訊息
============================================================================================
*/
namespace Messages
{
    // 移動不合法時
    void illegalMove()
    {
        cout << "Illegal move!" << endl;
    }
    // 攻擊不合法時
    void illegalAttack()
    {
        cout << "Illegal attack!" << endl;
    }
    // 升變不合法時
    void illegalPromotion()
    {
        cout << "Illegal promotion!" << endl;
    }
    // 入堡不合法時
    void IllegalCastling()
    {
        cout << "Illegal Castling!" << endl;
    }
    // 被將軍時
    void checkMate()
    {
        cout << "Checkmate!" << endl;
    }
    // 移動成功時
    void moveSuccess()
    {
        cout << "Move successful!" << endl;
    }
    // 升變成功時
    void promotionSuccess()
    {
        cout << "Promotion successful!" << endl;
    }
    // 對手無法移動該棋子
    void unableToMovePiece()
    {
        cout << "You can't move this Piece!" << endl;
    }

};
/*
============================================================================================
                                            棋盤
============================================================================================
*/
class Board
{
public:
    vector<vector<char>> board;
    Board()
    {
        init();
        cerr << "[DEBUG]<Function none>class:Board , Called Init!" << endl;
    } // 當class Board被宣告的時候 自動執行init 來初始化
    // ====================初始化棋盤====================
    void init()
    {
        board = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    }
    // ====================輸出棋盤====================
    void print() const
    {
        cout << "      W H I T E" << endl;   // 顯示白方
        cout << "  a b c d e f g h" << endl; // 顯示row 橫向
        // 顯示整個棋盤
        for (int i = 0; i < 8; ++i)
        {
            cout << 8 - i << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        // 顯示黑方
        cout << "     B L A C K" << endl;
    }
    // ====================判斷是否出界====================
    bool inBounds(char toRow, int toColumn) const
    { // 出界判斷
        // 這裡row判斷的是ASCII 碼 a = 97 , h = 104
        // 這裡col 只有1~8 行 所以偵測1~8
        if (toRow >= 97 && toRow < 105 && toColumn >= 1 && toColumn < 9)
        {
            // 通過的時候傳cerr , return 1
            cerr << "[DEBUG]<Function InBounds>class:Board , Passed row:" << toRow << " column: " << toColumn << endl;
            return 1;
        }
        // 沒通過的時候回傳錯誤訊息 然後傳row , col
        cerr << "[DEBUG] <Function InBounds>class:Board , Failed" << endl;
        cerr << "[DEBUG] toRow: " << toRow << " toColumn: " << toColumn << endl;
        return 0;
    }
    // ====================看是否已被佔領====================
    // 查看輸入的地址row , column 是否有棋子 有則返回true 否則 false
    bool isOccupied(char toRow, int toCol) const
    { // 是否有棋子
        if (board[8 - toCol][toRow - 'a'] == ' ')
        {
            cerr << "[DEBUG]<Function isOccupied>class:board , Row: " << toRow << " Column: " << toCol << endl;
            return 0; // 沒有棋子
        }
        cerr << "[DEBUG]<Function isOccoupied>class:Board , There's a piece at Row: " << toRow << " column: " << toCol << endl;
        cerr << "[DEBUG] Piece: " << board[8 - toCol][toRow - 'a'] << endl;
        return 1; // 有棋子
    }
    // ====================判斷是否同隊====================
    bool onSameTeam(char toRow, int toCol, bool isWhiteTurn) const
    { // 給canAttack 使用，判斷是否同隊
        cerr << "[DEBUG]<Function onSameTeam>class:Board , isWhiteTurn :" << isWhiteTurn << endl;
        if ((isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn) || (!(isupper(board[8 - toCol][toRow - 'a'])) && isWhiteTurn))
        {
            cerr << "[DEBUG]<Function onSameTeam>class:Board , Valid White: " << (isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn) << endl;
            cerr << "[DEBUG]<Function onSameTeam>class:Board , Valid Black: " << (!(isupper(board[8 - toCol][toRow - 'a'])) && isWhiteTurn) << endl;
            cerr << "[DEBUG]<Function onSameTeam>class:Board , onSameTeam check : true" << endl;
            return 1; // 同隊
        }
        cerr << "[DEBUG]<Function onSameTeam>class:Board , check passed -> result false" << endl;
        return 0; // 不同隊
    }
    // ====================判斷該棋子是否為現在輪到的選手可移動的====================
    bool canMovePiece(char fromRow, int fromCol, bool isWhiteTurn) const
    {
        char piece = board[8 - fromCol][fromRow - 'a'];
        if (piece == ' ' ||                  // 判斷是否為空
            isupper(piece) && isWhiteTurn || // 如果動的是uppercase 字母 然後又是白方
            !isupper(piece) && !isWhiteTurn) // 如果動非uppercase 又是黑方
        {
            // 都輸出沒辦法 然後return 0
            cerr << "[DEBUG]<Function canMovePiece>class:Board , Unable to Move Piece" << endl
                 << " Row: " << fromRow << " Col: " << fromCol << endl;
            cerr << "[DEBUG] Piece: " << board[8 - fromCol][fromRow - 'a'] << endl;
            cerr << "[DEBUG] isWhiteTurn: " << isWhiteTurn << endl;
            return 0; // 無法移動棋子
        }
        // 否則可以移動
        cerr << "[DEBUG]<Function canMovePiece>class:Board , Able to Move Piece Row: " << fromRow << " column: " << fromCol << endl;
        return 1; // 可以移動棋子
    }
    // ====================判斷是否為原地踏步====================
    bool isMove(char fromRow, int fromCol, char toRow, int toCol) const
    {
        // 這裡邏輯比較簡單
        cerr << "[DEBUG]<Function isMove>class:Board , Entered Function" << endl;
        if (fromRow == toRow && fromCol == toCol)
            return 0;
        return 1;
    }
    // ====================升變====================
    void promote(char toRow, int toCol, bool isWhiteTurn)
    { // 處理升變
        cerr << "[DEBUG]<Function Promote>class:Board ,Executed Promote System!" << endl;
        bool changed = false; // 如果有做改變
        if (!isWhiteTurn)
        {
            char piece;
            while (!changed)
            {
                cout << "Promote to (Q/R/B/N): ";
                cin >> piece;
                cerr << "[DEBUG]<Function Promote>class:Board , User chose: " << piece << endl;
                if (piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG]<Function (function Promote>class:Board , Updated!" << endl;
                    changed = true;
                }
                else
                    Messages::illegalPromotion(); // 不合法的升變
            }
        }
        else if (isWhiteTurn)
        {
            char piece;
            while (!changed)
            {
                cout << "Promote to (q/r/b/n): ";
                cin >> piece;
                cerr << "[DEBUG]<Function Promote>class:Board , User chose: " << piece << endl;
                if (piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG]<Function Promote>class:Board , Updated!" << endl;
                    changed = true;
                }
                else
                    Messages::illegalPromotion(); // 不合法的升變
            }
        }
        else
            cerr << "[DEBUG]<Function Promote>class:Board , Tell : The upper stuff didn't execute" << endl;
    }
    // ====================移動棋子====================
    void movePiece(char fromRow, int fromCol, char toRow, int toCol)
    { // 直接更新棋盤
        board[8 - toCol][toRow - 'a'] = board[8 - fromCol][fromRow - 'a'];
        board[8 - fromCol][fromRow - 'a'] = ' ';
    }
    // ====================看一路上是否皆為空==================== 水平 垂直版本
    // 這裡只檢查中間 開頭已檢查 不用檢查 , 尾部需要檢查 來判斷是否要攻擊
    bool isEmptyVerticalOrHorizontal(char fromRow, int fromCol, char toRow, int toCol, bool rowOrCol) const
    {
        // if check row then rowOrCol = 1 , else rowOrCol = 0
        if (rowOrCol)
        {
            int maxi = max(fromCol, toCol), mini = min(fromCol, toCol);
            for (int i = maxi - 1; i > mini; i--) // 不知道怎麼運作的 但運作了
            {
                if (isOccupied(toRow, i))
                    return 0;
            }
            return 1;
        }
        else
        {
            char maxi = (char)max(fromRow, toRow), mini = (char)min(fromRow, toRow);
            for (char i = maxi - 1; i > mini; i--)
            {
                if (isOccupied(i, toCol))
                    return 0;
            }
            return 1;
        }
        cerr << "[DEBUG]<Function isEmptyVerticalOrHorizontal>class:Board , Something went wrong" << endl;
        return 0;
    }
    // ====================看一路上是否為空==================== 斜對角版本
    bool isEmptyDiagonal(char fromRow, int fromCol, char toRow, int toCol)
    {
        cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board , Entered isEmptyDiagonal Function!" << endl;
        if (abs(fromRow - toRow) != abs(fromCol - toCol))
        {
            cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board ,fromRow - toRow = " << abs(fromRow - toRow) << " fromCol - toCol = " << abs(fromCol - toCol) << endl;
            return 0;
        }
        // 右下 -> fromRow + i, fromCol -i
        // 左上 -> fromRow - i, fromCol +i
        // 左下 -> fromRow - i ,fromCol -i
        // 右上 -> fromRow + i ,fromCol +i
        bool RightDown = false, LeftUp = false, LeftDown = false, RightUp = false, moveValid = true;
        if (toRow > fromRow && toCol < fromCol)
            RightDown = true;
        else if (toRow < fromRow && toCol > fromCol)
            LeftUp = true;
        else if (toRow < fromRow && toCol < fromCol)
            LeftDown = true;
        else if (toRow > fromRow && toCol > fromCol)
            RightUp = true;
        // for loop 再進入每個if 判斷
        for (int i = 1; i < abs(fromCol - toCol); i++)
        {
            if (RightDown && isOccupied(fromRow + i, fromCol - i))
            {
                cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board , RightDown for loop Error!" << endl;
                return 0;
            }
            else if (LeftUp && isOccupied(fromRow - i, fromCol + i))
            {
                cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board , LeftUp for loop Error!" << endl;
                return 0;
            }
            else if (LeftDown && isOccupied(fromRow - i, fromCol - i))
            {
                cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board , LeftDown for loop Error!" << endl;
                return 0;
            }
            else if (RightUp && isOccupied(fromRow + i, fromCol + i))
            {
                cerr << "[DEBUG]<Function isEmptyDiagonal>class:Board , RightUp for loop Error!" << endl;
                return 0;
            }
        }
        return 1;
    }
    // ====================看是什麼棋子====================
    char whatPieceisit(char fromRow, int fromCol)
    {
        char piece = board[8 - fromCol][fromRow - 'a'];

        cerr << "[DEBUG]<Function whatPieceisit>class:Board , Picked Piece:  " << piece << endl;
        return piece;
    }
};
/*
============================================================================================
                                            兵
============================================================================================
*/
// TODO 吃過路兵
class Pawn
{
public:
    // =====================是否可移動=====================
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    { // 如果不是同一行
        cerr << "[DEBUG]<Function canMove>class:Pawn , Executed Pawn canMove function!" << endl;
        bool firstMove = false;
        if (fromCol == 2 || 7)
            firstMove = true; // 給以後判斷移動是否合法
        if (fromRow != toRow) // 如果不同row
        {
            // 看是否能攻打
            if (fromCol == toCol) // 不同row 同col 代表橫向移動 不合法
            {
                cerr << "[DEBUG]<Function canMove>class:Pawn , horizontal Move" << endl;
                Messages::illegalMove();
                return 0;
            }
            // 判斷是否可攻擊 如果可以 則移動 否則返回
            if (canAttack(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                board.movePiece(fromRow, fromCol, toRow, toCol);
            else
            {
                cerr << "[DEBUG]<Function canMove>class:Pawn , Diagonal Move but can't attack" << endl;
                Messages::illegalMove();
                return false; // 不是斜對角
            }
            Messages::moveSuccess(); // 攻擊成功
            return true;
        }
        // printf("%s","this");
        // ----------------白方偵測----------------
        if (isWhiteTurn)
        {
            cerr << "[DEBUG]<Function canMove>class:Pawn , Pawn is WhiteTurn judging Executed!" << endl;
            if (fromCol - toCol != 1) // 因為是白方 所以是上到下 fromCol - toCol = 1 || 2
            {
                cerr << "[DEBUG]<Function canMove>class:Pawn , fromCol - toCol result = " << fromCol - toCol << endl;
                Messages::illegalMove();
                return 0;
            }
            else if (firstMove && fromCol - toCol != 2) // 第二次移動 可以移動兩格
            {
                cerr << "[DEBUG] fromCol - toCol result = " << fromCol - toCol << endl;
                Messages::illegalMove();
                return 0;
            }
        }
        // ----------------黑方偵測----------------
        else
        {
            cerr << "[DEBUG]<Function canMove>class:Pawn ,Pawn is BlackTurn judging Executed!" << endl;
            if (toCol - fromCol != 1) // 因為是白方 所以是上到下 toCol - fromCol = 1 || 2
            {
                cerr << "[DEBUG]<Function canMove>class:Pawn , toCol - fromCol result = " << toCol - fromCol << endl;
                Messages::illegalMove();
                return 0;
            }
            else if (firstMove && toCol - fromCol != 2) // 第二次移動 可以移動兩格
            {
                cerr << "[DEBUG]<Function canMove>class:Pawn , toCol - fromCol result = " << toCol - fromCol << endl;
                Messages::illegalMove();
                return 0;
            }
        }
        //  如果在格數移動都合法 那就進行再一步判斷
        if (board.isOccupied(toRow, toCol)) // 是否已被佔領
        {
            cerr << "[DEBUG]<Function canMove>class:Pawn ,Pawn toRow toCol is Occupied! Returning False" << endl;
            return false; // 假設這裡是偵測是有棋子
        }
        board.movePiece(fromRow, fromCol, toRow, toCol); // 移動棋子
        Messages::moveSuccess();
        if (canPromote(toCol)) // 看是不是可以升變
        {
            cerr << "[DEBUG]<Function canMove>class:Pawn , Executing Promoting Process!" << endl;
            board.promote(toRow, toCol, isWhiteTurn); // 處理升變
        } // 處理升變
        cerr << "[DEBUG]<Function canMove>class:Pawn , Returning True! Yeahoo" << endl;
        return true;
    }
    // =====================是否可攻擊=====================
    bool canAttack(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    {
        cerr << "[DEBUG]<Function canAttack>class:Pawn , Entered canAttack Function!" << endl;
        // ----------------偵測----------------
        cerr << "[DEBUG]<Function canAttack>class:Pawn , Judging if it is a diagonal move!" << endl;
        if (abs((fromRow - 'a') - (toRow - 'a')) == 1 && abs(fromCol - toCol) == 1) // 這裡看是否為斜對角
        {
            cerr << "[DEBUG]<Function canAttack>class:Pawn , canAttackJudging if toCol toRow have a piece" << endl;
            if (board.isOccupied(toRow, toCol)) // 這裡是偵測是否有棋子
            {
                cerr << "[DEBUG]<Function canAttack>class:Pawn , Judging if it is on  Same Team!" << endl;
                if (board.onSameTeam(toRow, toCol, isWhiteTurn)) // 這裡是偵測是否同隊
                {
                    Messages::illegalAttack();
                    return false; // 同隊不能攻擊
                }
                cerr << "[DEBUG]<Function canAttack>class:Pawn , Returning True!" << endl;
                return true; // 可以攻擊
            }
        }
        cerr << "[DEBUG]<Function canAttack>class:Pawn , Returning False (nooo )" << endl;
        return false;
    }
    // =====================是否可升變=====================
    bool canPromote(int toCol) const
    {
        cerr << "[DEBUG]<Function canPromote>class:Pawn , Entered canPromote Function" << endl;
        if (toCol == 1 || toCol == 8)
        {
            return 1; // 返回1代表可升變
        }
        else
            return 0;
    }
};
/*
============================================================================================
                                            車
============================================================================================
*/
// TODO 王車易位
class Rook
{
public:
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    {

        bool onSameRow = 0, onSameColumn = 0;
        if (fromRow == toRow)
            onSameRow = 1; // 代表要檢查column
        if (fromCol == toCol)
            onSameColumn = 1; // 代表要檢查row
        cerr << "[DEBUG]<Function canMove>class:Rook ,  onSameRow: " << onSameRow << " onSameColumn: " << onSameColumn << endl;
        if (onSameColumn && onSameRow)
        {
            Messages::illegalMove();
            return 0;
        }
        // onSameColumn -> 測row fromRow到toRow 中間是否為空
        // onSameRow 同理
        if (onSameColumn || onSameRow)
        { // row = 1 , col = 0
            cerr << "[DEBUG]<Function canMove>class:Rook , Entered the judging area of Rook!" << endl;
            bool rowOrCol = 1;
            bool empty = true; // 看是不是一路空
            if (onSameColumn)
            {
                rowOrCol = 1;
            }
            empty = board.isEmptyVerticalOrHorizontal(fromRow, fromCol, toRow, toCol, rowOrCol);
            if (!empty) // 如果 empty = 0
                return 0;
            // 如果是Empty , 看前往的地方是否有被佔領 以及是否在同隊
            if (board.isOccupied(toRow, toCol))
            {
                if (board.onSameTeam(toRow, toCol, isWhiteTurn))
                {
                    Messages::illegalMove();
                    return 0;
                }
            }
            // 移動
            board.movePiece(fromRow, fromCol, toRow, toCol);
            return 1;
        }
        // 如果上面條件事都沒進去那 我也不知道 就回傳0
        Messages::illegalMove();
        return 0;
    }
};
/*
============================================================================================
                                            馬
============================================================================================
*/
class Knight
{
public:
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        cerr << "[DEBUG]<Function canMove>class:Knight , Enter Knight canMove function!" << endl;
        bool moveValid = false; // 一開始初始化移動不合法
        if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 2 ||
            abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 1)
            moveValid = true; // 如果為日走路 則合法
        cerr << "[DEBUG]<Function canMove>class:Knight , moveValid = " << moveValid << endl;
        // 這裡不知道為甚麼要先檢查isOccupied , 效能有點降低 但沒關係
        // 如果Occupied 又onSameTeam 則return
        if (board.isOccupied(toRow, toCol))
        {
            cerr << "[DEBUG]<Function canMove>class:Knight , Enter Knight canMove function - isOccupied if judging,going for onSameTeam!" << endl;
            if (board.onSameTeam(toRow, toCol, isWhiteTurn))
            {
                cerr << "[DEBUG]<Function canMove>class:Knight , OnSameTeam equals true!" << endl;
                Messages::illegalMove();
                return 0;
            }
        }
        // 如果移動合法 那就movePiece
        if (moveValid)
        {
            board.movePiece(fromRow, fromCol, toRow, toCol);
            Messages::moveSuccess();
            return 1;
        }
        cerr << "[DEBUG]<Function canMove>class:Knight , moveValid isn't Valid!" << endl;
        Messages::illegalMove();
        return 0;
    }
};
/*
============================================================================================
                                            主教
============================================================================================
*/
class Bishop
{
public:
    // 主教移動規則為 斜對角走路 不能是直或橫
    // 所以下面兩個if 檢查是不是 非斜對角 如果是 則 return false
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        cerr << "[DEBUG]<Function canMove>class:Bishop , Entered Bishop canMove Function!" << endl;
        if (fromRow == toRow)
        {
            cerr << "[DEBUG]<Function Bishop>class:canMove , fromRow = toRow" << endl;
            Messages::illegalMove();
            return 0;
        }
        if (fromCol == toCol)
        {
            cerr << "[DEBUG]<Function canMove>class:Bishop , fromCol = toCol" << endl;
            Messages::illegalMove();
            return 0;
        }
        // 接下來檢查一路上是否都為空 前面有加! 所以會反轉boolean
        if (!(board.isEmptyDiagonal(fromRow, fromCol, toRow, toCol)))
            return 0;
        // 檢查是否被佔領又再同一行 則return false
        if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
        {
            cerr << "[DEBUG]<Function canMove>class:Bishop , OCCUPIED AND ONSAMETEAM ,RETURN 0" << endl;
            Messages::illegalMove();
            return 0;
            cerr << "[DEBUG]<Function canMove>class:Bishop , OCCUPIED BUT NOT ON SAMETEAM , canATTACK! , return 1" << endl;
        }
        board.movePiece(fromRow, fromCol, toRow, toCol);
        Messages::moveSuccess();
        return 1;
    }
};
/*
============================================================================================
                                            后
============================================================================================
*/
class Queen
{
public:
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        // 一開始get direciton 雖然是在class Queen 裡面不是 board 但 沒關係吧 哈哈 希望
        string direction = directionOfMove(fromRow, fromCol, toRow, toCol);
        // row = true , col = false
        // vertical = true , horizontal =  false
        bool rowOrCol = false;
        if (direction == "horizontal")
            rowOrCol = 0;
        else
            rowOrCol = 1;
        if (direction == "vertical" || direction == "horizontal")
        {
            if (!(board.isEmptyVerticalOrHorizontal(fromRow, fromCol, toRow, toCol, rowOrCol))) // 看一路上是否皆為空
            {
                cerr << "[DEBUG]<Function Queen>class:canMove , Queen vertical or horizontal if , error!" << endl;
                Messages::illegalMove();
                return 0;
            }
            // 被佔領 && 同隊 直接return false
            if (board.isOccupied(toRow, toCol))
            {
                if (board.onSameTeam(toRow, toCol, isWhiteTurn))
                {
                    Messages::illegalMove();
                    return 0;
                }
            }
            board.movePiece(fromRow, fromCol, toRow, toCol);
            return 1;
        }
        else if (direction == "diagonal")
        {
            // 斜對角移動 check 一路上是否為空
            if (!(board.isEmptyDiagonal(fromRow, fromCol, toRow, toCol)))
            {
                cerr << "[DEBUG]<Function canMove>class:Queen , Queen Diagonal if, error!" << endl;
                Messages::illegalMove();
                return 0;
            }
            if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
            {
                cerr << "[DEBUG]<Function canMove>class:Queen , OCCUPIED AND ONSAMETEAM ,RETURN 0" << endl;
                Messages::illegalMove();
                return 0;
                cerr << "[DEBUG]<Function canMove>class:Queen , OCCUPIED BUT NOT ON SAMETEAM , canATTACK! , return 1" << endl;
            }
            board.movePiece(fromRow, fromCol, toRow, toCol);
            Messages::moveSuccess();
            return 1;
        }
        return 0;
    }
    string directionOfMove(char fromRow, int fromCol, char toRow, int toCol)
    {
        if (fromRow == toRow && fromCol != toCol)
            return "vertical"; // fromRow = toRow -> 同一排 -> vertical 移動
        else if (fromRow != toRow && fromCol == toCol)
            return "horizontal"; // fromCol = toCol -> 同一列 ->horizontal 移動
        else
            return "diagonal";
        // 不知道這cerr是怎樣 哈哈 反正如果都不是就出錯 但應該不太可能
        cerr << "[DEBUG]<Function directionOfMove>class:Queen , Wtf just happened ? at Queen directionOfMove function" << endl;
        cerr << "[DEBUG]<Function directionOfMove>class:Queen ,fromRow = " << fromRow << " fromCol = " << fromCol << endl
             << " toRow = " << toRow << " toCol = " << toCol << endl;
        return 0;
    }
};
/*
============================================================================================
                                            王
============================================================================================
*/
class King
{
public:
    // 這裡還要補上 checkMate , castling , canMove or Attack
    bool canMoveAllJudge(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        // TODO 記得先判斷是否為castling 再進行canMove canAttack 判斷function
        
    }
    bool canMoveOrAttack(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        // fmt = from minus to , r = row , c = column
        // fromRow minus toRow , fromColumn minus to Column
        int fmtr = abs(fromRow - toRow), fmtc = abs(fromCol - toCol);
        if (fmtr > 1 || fmtc > 1)
            return 0;
        // 大於1 則return false
        // 被佔領又同隊 return 0
        if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
            return 0;
        return 1;
    }
    bool canCastling(Board &board, char fromRookRow, int fromRookCol, char fromKingRow, int fromKingCol)
    {
        cerr << "[DEBUG]<Function canCastling>class:King , Entered class King , Castling Function!" << endl;
        if (fromRookCol != fromKingCol) // 只有可能是橫向 不可能縱向 所以檢查col
        {
            cerr << "[DEBUG]<Function canCastling>class:King , fromRookCol != fromKingCol!" << endl;
            cerr << "[DEBUG]<Function canCastling>class:King , fromRookCol = " << fromRookCol << " fromKingCol = " << fromKingCol << endl;
            Messages::illegalMove();
            return 0;  
        }
        if (!(board.isEmptyVerticalOrHorizontal(fromRookRow, fromRookCol, fromKingRow, fromKingCol, 1)))
            return 0;
        Castling(board,fromRookRow,fromRookCol,fromKingRow,fromKingCol);
        return 1;
    }
    void Castling(Board &board,char fromRookRow,int fromRookCol,char fromKingRow,int fromKingCol)
    {
        int distances = abs(fromRookRow-fromKingRow);
        if(distances == 2) // 短易位
        {
            board.movePiece(fromKingRow,fromKingCol,fromKingRow+2,fromKingCol);
            board.movePiece(fromRookRow,fromRookCol,fromRookRow-2,fromRookCol);
        }
        else if(distances == 3) // 長易位
        {
            board.movePiece(fromKingRow,fromKingCol,fromKingRow-2,fromKingCol); // 向左移2格
            board.movePiece(fromRookRow,fromRookCol,fromRookRow+3,fromRookCol); // 向右移3格
        }
    }
};
class Game
{
public:
    // 這裡是尋找棋子
    pair<char, int> choosePiece(Board &board, bool isWhiteTurn) const
    {
        char row;
        int col;
        if (isWhiteTurn)
            cout << "White Turn!" << endl;
        else
            cout << "Black Turn!" << endl;
        cout << "Enter the coordinate to move!(row,col)" << endl;
        cin >> row >> col;
        pair<char, int> p;
        p.first = row;
        p.second = col;

        return p;
    }
    bool judgePiecesCanMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn, char piece) const
    {
        if (piece == 'r' || piece == 'R')
        {
            Rook rook;
            rook.canMove(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else if (piece == 'q' || piece == 'Q')
        {
            Queen queen;
            queen.canMove(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else if (piece == 'b' || piece == 'B')
        {
            Bishop bishop;
            bishop.canMove(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else if (piece == 'p' || piece == 'P')
        {
            Pawn pawn;
            pawn.canMove(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else if (piece == 'k' || piece == 'K')
        {
            King king;
            king.canMoveAllJudge(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else if (piece == 'n' || piece == 'N')
        {
            Knight knight;
            knight.canMove(board, fromRow, fromCol, toRow, toCol, isWhiteTurn);
        }
        else
            return 0;
    }
    // 這裡主要是get 使用者輸入data
    pair<char, int> moveToCoordinate()
    {
        char row;
        int col;
        cout << "Enter the coordinate to move to!(row,col)" << endl;
        cin >> row >> col;
        pair<char, int> p;
        p.first = row;
        p.second = col;
        return p;
    }
};
/*
============================================================================================
                                            主要
============================================================================================
*/
int main()
{
    // 這裡需要判斷是否inbound && canMovePiece!
    // if 第一個座標 && 第二個座標 都為同一方 && King + Rook -> 額外判斷
    // 這裡需要有have RR(h,1) RL(a,1) ,rR(h,8) rL(a,8) 有動 為了Castling
    bool rerun = true; // 一開始預設重新開局
    char reRunorNot;   // 一開始設 最後會用
    while (rerun)
    {
        char GameStartOrNo;
        bool startGame = false;
        cout << "Welcome to Western Chess Game!" << endl;
        cout << "Do you want to start the game? (y/n):";
        cin >> GameStartOrNo;
        while (GameStartOrNo != 'y' && GameStartOrNo != 'n')
        {
            // GameStartOrNo != 'y' or 'n' return 0
            cout << "Invalid choice , rechoose y or n" << endl;
            cout << "Do you want to start the game? (y/n):";
            cin >> GameStartOrNo;
        }
        if (GameStartOrNo == 'n')
        {
            // GameStartOrNo  = 'n' -> return false
            cout << "Alright! See you!" << endl;
            return false;
        }
        if (GameStartOrNo == 'y')
            startGame = true;
        while (startGame)
        {
            // 先把一些變數設好
            bool isWhiteTurn = false, start = false, Black_King_Alive = true, White_King_Alive = true, isCastling = false;

            string whoGoesFirst;
            cout << "Who goes  first? (Black/White):";
            cin >> whoGoesFirst;
            for(int i=0;i<5;i++)
            toupper(whoGoesFirst[i]);
            // 把每個都變成大寫 避免嚴格輸入
            if (whoGoesFirst == "WHITE" || whoGoesFirst == "BLACK")
                start = true;
            if (whoGoesFirst == "WHITE")
                isWhiteTurn = true;
            if (!start)
            {
                cout << "Rechoose Black or White" << endl;
                continue; // 重複回到while
            }
            while (start)
            {
                Board board;
                Game game;
                vector<vector<char>> PreviousBoard = board.board; // 這裡算是有點懶吧 哈哈 紀錄上一回合的棋盤
                // 先設好變數
                bool whiteLeftRook = false, whiteRightRook = false, blackLeftRook = false, blackRightRook = false;
                while (Black_King_Alive && White_King_Alive)
                {
                    pair<char, int> pieceToMove; // 選棋移動
                    board.print();
                    pieceToMove = game.choosePiece(board, isWhiteTurn);
                    // 這裡用兩個判斷 一起判斷 其中一個不合格直接重新
                    while (!(board.inBounds(pieceToMove.first, pieceToMove.second)) || !(board.canMovePiece(pieceToMove.first, pieceToMove.second, isWhiteTurn)))
                        pieceToMove = game.choosePiece(board, isWhiteTurn);
                    pair<char, int> positionToMoveTo;
                    board.print();
                    positionToMoveTo = game.moveToCoordinate();
                    while (!(board.inBounds(positionToMoveTo.first, positionToMoveTo.second)))
                        positionToMoveTo = game.moveToCoordinate();
                    char movePiece = board.whatPieceisit(pieceToMove.first, pieceToMove.second);
                    // ================兵================
                    if (movePiece == 'p' || movePiece == 'P')
                    {
                        Pawn pawn;
                        if (!(pawn.canMove(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    // ================后================
                    else if (movePiece == 'q' || movePiece == 'Q')
                    {
                        Queen queen;
                        if (!(queen.canMove(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    // ================象================
                    else if (movePiece == 'b' || movePiece == 'B')
                    {
                        Bishop bishop;
                        if (!(bishop.canMove(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    // ================馬================
                    else if (movePiece == 'n' || movePiece == 'N')
                    {
                        Knight knight;
                        if (!(knight.canMove(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    // ================王================
                    else if (movePiece == 'k' || movePiece == 'K')
                    {
                        King king;
                        if (!(king.canMoveAllJudge(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    // ================車================
                    else if (movePiece == 'r' || movePiece == 'R')
                    {
                        Rook rook;
                        if (!(rook.canMove(board, pieceToMove.first, pieceToMove.second, positionToMoveTo.first, positionToMoveTo.second, isWhiteTurn)))
                            continue;
                    }
                    isWhiteTurn = !isWhiteTurn;
                    // 確保不是王車易位
                    if (!isCastling)
                    {
                        cerr << "[DEBUG]<Function Main>class:Main , Not Castling! Judging if got attack piece is King" << endl;
                        // 這裡看攻擊的棋子是否是王 代表被攻擊 被吃掉
                        if (PreviousBoard[(positionToMoveTo.first - 'a')][(8 - positionToMoveTo.second)] == 'k')
                            White_King_Alive = false;
                        else if (PreviousBoard[(8 - positionToMoveTo.second)][(positionToMoveTo.first - 'a')] == 'K')
                            Black_King_Alive = false;
                    }
                    // 接下來判斷王活著還是沒活著
                    cerr << "[DEBUG]<Function Main>class:Main , Black King Alive: " << Black_King_Alive << endl;
                    cerr << "[DEBUG]<Function Main>class:Main , White King Alive: " << White_King_Alive << endl;
                    if (!White_King_Alive)
                    {
                        start = false;
                        startGame = false;
                        cout << "Game End!" << endl;
                        cout << "Black Won the Game!" << endl;
                    }
                    else if (!Black_King_Alive)
                    {
                        start = false;
                        startGame = false;
                        cout << "Game End!" << endl;
                        cout << "White Won the Game!" << endl;
                    }
                }
            }
        }
        // 對局結束 看要不要新的一盤局
        cout << "Start a new game?(y/n)" << endl;
        cin >> reRunorNot;
        if (reRunorNot == 'n')
            rerun = false;
    }
    return 0;
}
