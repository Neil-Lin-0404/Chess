// TODO 到時候新增顏色
// Started Making Date : 2025/7/1
// board[8- toCol][toRow - 'a'] (Important)
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
    void illegalMove()
    {
        cout << "Illegal move!" << endl;
    }
    void illegalAttack()
    {
        cout << "Illegal attack!" << endl;
    }
    void illegalPromotion()
    {
        cout << "Illegal promotion!" << endl;
    }
    void illegalCastle()
    {
        cout << "Illegal castle!" << endl;
    }
    void checkMate()
    {
        cout << "Checkmate!" << endl;
    }
    void moveSuccess()
    {
        cout << "Move successful!" << endl;
    }
    void promotionSuccess()
    {
        cout << "Promotion successful!" << endl;
    }
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
    vector<vector<char>> board =
        {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'b', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    // Board() { init(); }
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
        cout << "      W H I T E" << endl;
        cout << "  a b c d e f g h" << endl;
        for (int i = 0; i < 8; ++i)
        {
            cout << 8 - i << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "     B L A C K" << endl;
    }
    // ====================判斷是否出界====================
    bool inBounds(char toRow, int toColumn) const
    { // 出界判斷
        if (toRow >= 97 && toRow < 105 && toColumn >= 1 && toColumn < 9)
        {
            cerr << "[DEBUG] InBounds check passed row:" << toRow << " column: " << toColumn << endl;
            return 1;
        }
        cerr << "[DEBUG] InBounds check failed" << endl;
        cerr << "[DEBUG] toRow: " << toRow << " toColumn: " << toColumn << endl;
        Messages::illegalMove();
        return 0;
    }
    // 查看輸入的地址row , column 是否有棋子 有則返回true 否則 false
    // ====================看是否已被佔領====================
    bool isOccupied(char toRow, int toCol) const
    { // 是否有棋子
        if (board[8 - toCol][toRow - 'a'] == ' ')
        {
            cerr << "[DEBUG] There is no piece at row: " << toRow << " column: " << toCol << endl;
            return 0; // 沒有棋子
        }
        cerr << "[DEBUG] There is a piece at row: " << toRow << " column: " << toCol << endl;
        cerr << "[DEBUG] Piece: " << board[8 - toCol][toRow - 'a'] << endl;
        return 1;
    }
    // ====================判斷是否同隊====================
    bool onSameTeam(char toRow, int toCol, bool isWhiteTurn) const
    { // 給canAttack 使用，判斷是否同隊
        if (isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn || !(isupper(board[8 - toCol][toRow - 'a']) && isWhiteTurn))
        {
            cerr << "[DEBUG] on Same Team check , result : true" << endl;
            return 1; // 同隊
        }
        cerr << "[DEBUG] on Same Team check , result : false" << endl;
        return 0;
    }
    // ====================判斷該棋子是否為現在輪到的選手可移動的====================
    bool canMovePiece(char fromRow, int fromCol, bool isWhiteTurn) const
    {
        char piece = board[8 - fromCol][fromRow - 'a'];
        if (piece == ' ' ||
            isupper(piece) && isWhiteTurn ||
            !isupper(piece) && !isWhiteTurn)
        {
            cerr << "[DEBUG] Unable to move Piece" << endl
                 << " Row: " << fromRow << " Col: " << fromCol << endl;
            cerr << "[DEBUG] Piece: " << board[8 - fromCol][fromRow - 'a'] << endl;
            cerr << "[DEBUG] isWhiteTurn: " << isWhiteTurn << endl;
            return 0; // 無法移動棋子
        }
        cerr << "[DEBUG] Able to Move piece row: " << fromRow << " column: " << fromCol << endl;
        return 1; // 可以移動棋子
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
    // ====================看一路上是否皆為空====================
    // 這裡只檢查中間 開頭已檢查 不用檢查 , 尾部需要檢查 來判斷是否要攻擊
    bool isEmpty(char fromRow, int fromCol, char toRow, int toCol, bool rowOrCol)
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
        cerr << "[DEBUG] Something went wrong at (class : Board, isEmpty Function!)" << endl;
        return 0;
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
            if (fromCol - toCol != 1) // 因為是白方 所以是上到下 fromCol - toCol = 1
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
            if (toCol - fromCol != 1) // 因為是黑方 所以是下到上 toCol - fromCol = 1
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
        // ----------------白方偵測----------------
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
       
        bool onSameRow, onSameColumn;
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
            empty = board.isEmpty(fromRow, fromCol, toRow, toCol, rowOrCol);
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
        if (abs(fromRow - toRow) != abs(fromCol - toCol))
        {
            cerr << "[DEBUG] fromRow - toRow = " << abs(fromRow - toRow) << " fromCol - toCol = " << abs(fromCol - toCol) << endl;
            Messages::illegalMove();
            return 0;
        }
        // 右下 -> fromRow + i, fromCol -i
        // 左上 -> fromRow - i, fromCol +i
        // 左下 -> fromRow - i ,fromCol -i
        // 右上 -> fromRow + i ,fromCol +i
        bool RightDown = false, LeftUp = false, LeftDown = false, RightUp = false,moveValid=true;
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
            if(RightDown)
            {
                if(board.isOccupied(fromRow+i,fromCol -i))
                {
                    cerr << "[DEBUG] RightDown for loop Error!"<<endl;
                    Messages::illegalMove();
                    return 0;
                }
            }
            else if(LeftUp)
            {
                if(board.isOccupied(fromRow-i,fromCol +i))
                {
                    cerr << "[DEBUG] LeftUp for loop Error!"<<endl;
                    Messages::illegalMove();
                    return 0;
                }
            }
            else if(LeftDown)
            {
                if(board.isOccupied(fromRow-i,fromCol -i))
                {
                    cerr << "[DEBUG] LeftDown for loop Error!"<<endl;
                    Messages::illegalMove();
                    return 0;
                }
            }
            else if(RightUp)
            {
                if(board.isOccupied(fromRow+i,fromCol +i))
                {
                    cerr << "[DEBUG] RightUp for loop Error!"<<endl;
                    Messages::illegalMove();
                    return 0;
                }
            }
        }
        if(board.isOccupied(toRow,toCol))
        {
            if(board.onSameTeam(toRow,toCol,isWhiteTurn))
            {
                cerr << "[DEBUG] OCCUPIED AND ONSAMETEAM ,RETURN 0" << endl;
                Messages::illegalMove();
                return 0;
            }
            cerr << "[DEBUG] OCCUPIED BUT NOT ON SAMETEAM , canATTACK! , return 1" << endl;
        }
        board.movePiece(fromRow,fromCol,toRow,toCol);
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
};
/*
============================================================================================
                                            王
============================================================================================
*/
class King
{
public:
};
/*
============================================================================================
                                            主要
============================================================================================
*/
int main()
{
    // 這裡需要判斷是否inbound && canMovePiece!
    Board chessBoard;
    chessBoard.print();
    Bishop bishop;
    bishop.canMove(chessBoard,'a',7,'c',5,0);
    chessBoard.print();
    return 0;
}


