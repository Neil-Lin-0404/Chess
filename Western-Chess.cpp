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
    Board() { init();
    cerr << "[DEBUG]<Function none>class:Board , Called Init!"<<endl; } // 當class Board被宣告的時候 自動執行init 來初始化
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
        cout << "      W H I T E" << endl; // 顯示白方
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
        cerr << "[DEBUG] InBounds check failed" << endl;
        cerr << "[DEBUG] toRow: " << toRow << " toColumn: " << toColumn << endl;
        return 0;
    }
    // ====================看是否已被佔領====================
    // 查看輸入的地址row , column 是否有棋子 有則返回true 否則 false
    bool isOccupied(char toRow, int toCol) const
    { // 是否有棋子
        if (board[8 - toCol][toRow - 'a'] == ' ')
        {
            cerr << "[DEBUG] There is no piece at row: " << toRow << " column: " << toCol << endl;
            return 0; // 沒有棋子
        }
        cerr << "[DEBUG] There is a piece at row: " << toRow << " column: " << toCol << endl;
        cerr << "[DEBUG] Piece: " << board[8 - toCol][toRow - 'a'] << endl;
        return 1; // 有棋子
    }
    // ====================判斷是否同隊====================
    bool onSameTeam(char toRow, int toCol, bool isWhiteTurn) const
    { // 給canAttack 使用，判斷是否同隊
        cerr << "[DEBUG] isWhite Turn :" << isWhiteTurn << endl;
        if ((isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn) || (!(isupper(board[8 - toCol][toRow - 'a'])) && isWhiteTurn))
        {
            cerr << "[DEBUG]: "<<(isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn) <<endl;
            cerr << "[DEBUG]: " << (!(isupper(board[8 - toCol][toRow - 'a'])) && isWhiteTurn) << endl;
            cerr << "[DEBUG] on Same Team check , result : true" << endl;
            return 1; // 同隊
        }
        cerr << "[DEBUG] on Same Team check , result : false" << endl;
        return 0; // 不同隊
    }
    // ====================判斷該棋子是否為現在輪到的選手可移動的====================
    bool canMovePiece(char fromRow, int fromCol, bool isWhiteTurn) const
    {
        char piece = board[8 - fromCol][fromRow - 'a'];
        if (piece == ' ' || //判斷是否為空
            isupper(piece) && isWhiteTurn || // 如果動的是uppercase 字母 然後又是白方
            !isupper(piece) && !isWhiteTurn) // 如果動非uppercase 又是黑方
        {
            // 都輸出沒辦法 然後return 0
            cerr << "[DEBUG] Unable to move Piece" << endl
                 << " Row: " << fromRow << " Col: " << fromCol << endl;
            cerr << "[DEBUG] Piece: " << board[8 - fromCol][fromRow - 'a'] << endl;
            cerr << "[DEBUG] isWhiteTurn: " << isWhiteTurn << endl;
            return 0; // 無法移動棋子
        }
        // 否則可以移動
        cerr << "[DEBUG] Able to Move piece row: " << fromRow << " column: " << fromCol << endl;
        return 1; // 可以移動棋子
    }
    // ====================判斷是否為原地踏步====================
    bool isMove(char fromRow,int fromCol,char toRow,int toCol)const
    {
        // 這裡邏輯比較簡單
        cerr << "[DEBUG]<Function isMove>class:Board , Entered Function"<<endl;
        if(fromRow == toRow && fromCol == toCol)return 0;
        return 1;
    }
    // ====================升變====================
    void promote(char toRow, int toCol, bool isWhiteTurn)
    { // 處理升變
        cerr << "[DEBUG] Executed Promote System!" << endl;
        bool changed = false;
        if (!isWhiteTurn)
        {
            char piece;
            while (!changed)
            {
                cout << "Promote to (Q/R/B/N): ";
                cin >> piece;
                cerr << "[DEBUG] User chose: " << piece << endl;
                if (piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG] Updated!" << endl;
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
                cerr << "[DEBUG] User chose: " << piece << endl;
                if (piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG] Updated!" << endl;
                    changed = true;
                }
                else
                    Messages::illegalPromotion(); // 不合法的升變
            }
        }
        else
            cerr << "[DEBUG] The upper stuff didn't execute" << endl;
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
            for (int i = maxi - 1; i > mini; i--)
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
        cerr << "[DEBUG] Something went wrong at (class : Board, isEmptyVerticalOrHorizontal Function!)" << endl;
        return 0;
    }
    // ====================看一路上是否為空==================== 斜對角版本
    bool isEmptyDiagonal(char fromRow, int fromCol, char toRow, int toCol)
    {
        cerr << "[DEBUG] Entered isEmptyDiagonal Function!" << endl;
        if (abs(fromRow - toRow) != abs(fromCol - toCol))
        {
            cerr << "[DEBUG] fromRow - toRow = " << abs(fromRow - toRow) << " fromCol - toCol = " << abs(fromCol - toCol) << endl;
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
        for (int i = 1; i < abs(fromCol - toCol); i++)
        {
            if (RightDown && isOccupied(fromRow + i, fromCol - i))
            {
                cerr << "[DEBUG] RightDown for loop Error!" << endl;
                return 0;
            }
            else if (LeftUp && isOccupied(fromRow - i, fromCol + i))
            {
                cerr << "[DEBUG] LeftUp for loop Error!" << endl;
                return 0;
            }
            else if (LeftDown && isOccupied(fromRow - i, fromCol - i))
            {
                cerr << "[DEBUG] LeftDown for loop Error!" << endl;
                return 0;
            }
            else if (RightUp && isOccupied(fromRow + i, fromCol + i))
            {
                cerr << "[DEBUG] RightUp for loop Error!" << endl;
                return 0;
            }
        }
        return 1;
    }
    char whatPieceisit(char fromRow, int fromCol)
    {
        char piece = board[8 - fromCol][fromRow - 'a'];
        
        cerr << "[DEBUG] What piece is it:  " << piece <<  endl;
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
        cerr << "[DEBUG] Executed Pawn canMove function!" << endl;

        if (fromRow != toRow)
        {
            // 看是否能攻打
            if (fromCol == toCol)
            {
                cerr << "[DEBUG] Illegal Move at Pawn canMove , second if (fromCol == toCol)" << endl;
                Messages::illegalMove();
                return 0;
            }
            if (canAttack(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                board.movePiece(fromRow, fromCol, toRow, toCol);
            else
            {
                cerr << "[DEBUG] Pawn canMove at First if-> second if-> else" << endl;
                Messages::illegalMove();
                return false; // 不是斜對角
            }
            Messages::moveSuccess();
            return true;
        }
        // ----------------白方偵測----------------
        if (isWhiteTurn)
        {
            cerr << "[DEBUG] Pawn is WhiteTurn judging Executed!" << endl;
            if (fromCol - toCol != 1 &&fromCol - toCol != 2) // 因為是白方 所以是上到下 fromCol - toCol = 1 || 2
            {
                cerr << "[DEBUG] fromCol - toCol result = " << fromCol - toCol << endl;
                Messages::illegalMove();
                return 0;
            }
        }
        // ----------------黑方偵測----------------
        else
        {
            cerr << "[DEBUG] Pawn is BlackTurn judging Executed!" << endl;
            if (toCol - fromCol != 1&&toCol - fromCol != 2) // 因為是黑方 所以是下到上 toCol - fromCol = 1 || 2
            {
                Messages::illegalMove();
                return 0;
            }
        }
        if (board.isOccupied(toRow, toCol))
        {
            cerr << "[DEBUG] Pawn toRow toCol is Occupied! Returning False" << endl;
            return false; // 假設這裡是偵測是有棋子
        }
        board.movePiece(fromRow, fromCol, toRow, toCol); // 移動棋子
        Messages::moveSuccess();
        if (canPromote(toCol))
        {
            cerr << "[DEBUG] Executing Promoting Process!" << endl;
            board.promote(toRow, toCol, isWhiteTurn); // 處理升變
        } // 處理升變
        cerr << "[DEBUG] Returning True! Yeahoo" << endl;
        return true;
    }
    // =====================是否可攻擊=====================
    bool canAttack(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    {
        cerr << "[DEBUG] Entered canAttack Function!" << endl;
        // ----------------偵測----------------
        cerr << "[DEBUG] Judging if it is a diagonal move!" << endl;
        if (abs((fromRow - 'a') - (toRow - 'a')) == 1 && abs(fromCol - toCol) == 1) // 這裡看是否為斜對角
        {
            cerr << "[DEBUG] Judging if toCol toRow have a piece" << endl;
            if (board.isOccupied(toRow, toCol)) // 這裡是偵測是否有棋子
            {
                cerr << "[DEBUG] Judging if it is on  Same Team!" << endl;
                if (board.onSameTeam(toRow, toCol, isWhiteTurn)) // 這裡是偵測是否同隊
                {
                    Messages::illegalAttack();
                    return false; // 同隊不能攻擊
                }
                cerr << "[DEBUG] Returning True!" << endl;
                return true; // 可以攻擊
            }
        }
        cerr << "[DEBUG] Returning False (nooo )" << endl;
        return false;
    }
    // =====================是否可升變=====================
    bool canPromote(int toCol) const
    {
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

        bool onSameRow=0, onSameColumn=0;
        if (fromRow == toRow)
            onSameRow = 1; // 代表要檢查column
        if (fromCol == toCol)
            onSameColumn = 1; // 代表要檢查row
        cerr << "[DEBUG] onSameRow: " << onSameRow << " onSameColumn: " << onSameColumn << endl;
        if (onSameColumn && onSameRow)
        {
            Messages::illegalMove();
            return 0;
        }
        // onSameColumn -> 測row fromRow到toRow 中間是否為空
        // onSameRow 同理
        if (onSameColumn || onSameRow)
        {
            cerr << "[DEBUG] Entered the judging area of Rook!" << endl;
            bool rowOrCol = 1;
            bool empty = true;
            if (onSameColumn)
            {
                rowOrCol = 1;
            }
            empty = board.isEmptyVerticalOrHorizontal(fromRow, fromCol, toRow, toCol, rowOrCol);
            if (!empty)
                return 0;
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
        cerr << "[DEBUG] Enter Knight canMove function!" << endl;
        bool moveValid = false;
        if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 2 ||
            abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 1)
            moveValid = true;
        cerr << "[DEBUG] moveValid = " << moveValid << endl;
        if (board.isOccupied(toRow, toCol))
        {
            cerr << "[DEBUG] Enter Knight canMove function - isOccupied if judging,going for onSameTeam!" << endl;
            cerr << "[DEBUG] Should be not OnSameTeam if attack" << endl;
            if (board.onSameTeam(toRow, toCol, isWhiteTurn))
            {
                cerr << "[DEBUG] OnSameTeam function executed! of Knight onSameTeam!" << endl;
                Messages::illegalMove();
                return 0;
            }
        }
        if (moveValid)
        {
            board.movePiece(fromRow, fromCol, toRow, toCol);
            Messages::moveSuccess();
            return 1;
        }
        cerr << "[DEBUG] moveValid isn't Valid!" << endl;
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
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        cerr << "[DEBUG] Entered Bishop canMove Function!" << endl;
        if (fromRow == toRow)
        {
            cerr << "[DEBUG] fromRow = toRow" << endl;
            Messages::illegalMove();
            return 0;
        }
        if (fromCol == toCol)
        {
            cerr << "[DEBUG] fromCol = toCol" << endl;
            Messages::illegalMove();
            return 0;
        }
        if (!(board.isEmptyDiagonal(fromRow, fromCol, toRow, toCol)))
            return 0;
        if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
        {
            cerr << "[DEBUG] OCCUPIED AND ONSAMETEAM ,RETURN 0" << endl;
            Messages::illegalMove();
            return 0;
            cerr << "[DEBUG] OCCUPIED BUT NOT ON SAMETEAM , canATTACK! , return 1" << endl;
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
        string direction = directionOfMove(fromRow, fromCol, toRow, toCol);
        bool rowOrCol;
        if (direction == "horizontal")
            rowOrCol = 0;
        else
            rowOrCol = 1;
        if (direction == "vertical" || direction == "horizontal")
        {
            if (!(board.isEmptyVerticalOrHorizontal(fromRow, fromCol, toRow, toCol, rowOrCol)))
            {
                cerr << "[DEBUG] Queen vertical or horizontal if , error!" << endl;
                Messages::illegalMove();
                return 0;
            }
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
            if (!(board.isEmptyDiagonal(fromRow, fromCol, toRow, toCol)))
            {
                cerr << "[DEBUG] Queen Diagonal if, error!" << endl;
                Messages::illegalMove();
                return 0;
            }
            if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
            {
                cerr << "[DEBUG] OCCUPIED AND ONSAMETEAM ,RETURN 0" << endl;
                Messages::illegalMove();
                return 0;
                cerr << "[DEBUG] OCCUPIED BUT NOT ON SAMETEAM , canATTACK! , return 1" << endl;
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
            return "vertical";
        else if (fromRow != toRow && fromCol == toCol)
            return "horizontal";
        else
            return "diagonal";
        cerr << "[DEBUG] Wtf just happened ? at Queen directionOfMove function" << endl;
        cerr << "[DEBUG]fromRow = " << fromRow << " fromCol = " << fromCol << endl
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
    bool canMoveAllJudge(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
    }
    bool canMoveOrAttack(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn)
    {
        int fmtr = abs(fromRow - toRow), fmtc = abs(fromCol - toCol);
        if (fmtr > 1 || fmtc > 1)
            return 0;
        if (board.isOccupied(toRow, toCol) && board.onSameTeam(toRow, toCol, isWhiteTurn))
            return 0;
        return 1;
    }
    bool canCastling(Board &board, char fromRookRow, int fromRookCol, char fromKingRow, int fromKingCol)
    {
        cerr << "[DEBUG] Entered class King , Castling Function!" << endl;
        if (fromRookCol != fromKingCol)
        {
            cerr << "[DEBUG] fromRookCol != fromKingCol!" << endl;
            cerr << "[DEBUG] fromRookCol = " << fromRookCol << " fromKingCol = " << fromKingCol << endl;
            Messages::illegalMove();
            return 0;
        }
        if (!(board.isEmptyVerticalOrHorizontal(fromRookRow, fromRookCol, fromKingRow, fromKingCol, 1)))
            return 0;

        return 1;
    }
};
class Game
{
public:
    bool choosePiece(Board&board ,char fromRow,int fromCol,char toRow,int toCol,bool isWhiteTurn)const
    {
        char row;
        int col;
        if(isWhiteTurn) cout << "White Turn!" << endl;
        else cout << "Black Turn!" << endl;
        cout << "Enter the coordinate to move!(row,col)" << endl;
        cin >> row >> col;
        pair<char, int> p;
        p.first = row;
        p.second = col;
        char piece = board.board[8- p.second][p.first - 'a'];
        bool canOrNot = judgePiecesCanMove(board ,fromRow,fromCol,toRow,toCol,isWhiteTurn,piece);

    }
    bool judgePiecesCanMove(Board &board ,char fromRow,int fromCol,char toRow,int toCol,bool isWhiteTurn,char piece)const
    {
        if(piece == 'r' || piece == 'R')
        {
            Rook rook;
            rook.canMove(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else if(piece == 'q' || piece == 'Q')
        {
            Queen queen;
            queen.canMove(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else if(piece == 'b' || piece == 'B')
        {
            Bishop bishop;
            bishop.canMove(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else if(piece == 'p' || piece == 'P')
        {
            Pawn pawn;
            pawn.canMove(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else if(piece == 'k' || piece == 'K')
        {
            King king;
            king.canMoveAllJudge(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else if(piece == 'n' || piece == 'N')
        {
            Knight knight;
            knight.canMove(board,fromRow,fromCol,toRow,toCol,isWhiteTurn);
        }
        else
        return 0;
    }
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
    bool rerun = true;
    char reRunorNot;
    while (rerun)
    {
        char GameStartOrNo;
        bool startGame = false;
        cout << "Welcome to Western Chess Game!" << endl;
        cout << "Do you want to start the game? (y/n):";
        cin >> GameStartOrNo;
        while (GameStartOrNo != 'y' && GameStartOrNo != 'n')
        {
            cout << "Invalid choice , rechoose y or n" << endl;
            cout << "Do you want to start the game? (y/n):";
            cin >> GameStartOrNo;
        }
        if (GameStartOrNo == 'n')
        {
            cout << "Alright! See you!" << endl;
            return 0;
        }
        if (GameStartOrNo == 'y')
            startGame = true;
        while (startGame)
        {
            bool isWhiteTurn = false, start = false, Black_King_Alive = true, White_King_Alive = true, isCastling = false;
            string whoGoesFirst;
            cout << "Who goes  first? (Black/White):";
            cin >> whoGoesFirst;
            if (whoGoesFirst == "White" || whoGoesFirst == "Black")
                start = true;
            if (whoGoesFirst == "White")
                isWhiteTurn = 1;
            if (!start)
            {
                cout << "Rechoose black or white" << endl;
                continue;
            }
            while (start)
            {
                Board board;
                Game game;
                vector<vector<char>> PreviousBoard = board.board;
                bool whiteLeftRook = false, whiteRightRook = false, blackLeftRook = false, blackRightRook = false;
                while (Black_King_Alive && White_King_Alive)
                {
                    pair<char, int> pieceToMove;
                    board.print();
                    pieceToMove = game.choosePiece(isWhiteTurn);
                    while (!(board.inBounds(pieceToMove.first, pieceToMove.second)) || !(board.canMovePiece(pieceToMove.first, pieceToMove.second, isWhiteTurn)))
                        pieceToMove = game.choosePiece(isWhiteTurn);
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
                        cerr << "[DEBUG] Not Castling! Judging if got attack piece is King" << endl;
                        // 這裡看攻擊的棋子是否是王 代表被攻擊 被吃掉
                        if (PreviousBoard[(positionToMoveTo.first-'a')][(8-positionToMoveTo.second)] == 'k')
                            White_King_Alive = false;
                        else if (PreviousBoard[(8-positionToMoveTo.second)][(positionToMoveTo.first-'a')] == 'K')
                            Black_King_Alive = false;
                    }
                    cerr << "[DEBUG] Black King Alive: " << Black_King_Alive << endl;
                    cerr << "[DEBUG] White King Alive: " << White_King_Alive << endl;
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

        cout << "Start a new game?(y/n)" << endl;
        cin >> reRunorNot;
        if (reRunorNot == 'n')
            rerun = false;
    }
    return 0;
}
// Known Bugs! 
/* 
King detect alive or not ✅
原地踏步
pawn 非第一步卻可以走兩步
*/
