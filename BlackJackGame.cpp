#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

enum Rank
{
    ACE = 1, TWO, THREE, FOUR,
    FIVE, SIX, SEVEN, EIGHT,
    NINE, TEN, JACK, QUEEN, KING
};

enum Type
{
    CLUBS, DIAMONDS, HEARTS, SPADES
};

class Card
{
private:
    Rank rank;
    Type type;

public:
    Card();
    Card(Rank rank, Type type);
    ~Card();
    int getValue();
    void displayCard();
};

Card::Card()
{
    // nothing 
}

Card::Card(Rank rank, Type type):
    rank(rank), type(type)
{
    // nothing to add here
}

Card::~Card()
{
    // nothing to add here
}

int Card::getValue()
{
    // ACE's default value is 11 unless it busts
    if (rank == 1)
        return 11;
    // TEN, JACK, QUEEN, and KING all have value of 10
    if (rank >= 10)
        return 10;
    return rank;
}

/*  This function is used to output player
 *  hand's card information.
 *  The output will start with the face 
 *  value (from 1 to K), followed by 
 *  the first character of its suit.
 */
void Card::displayCard()
{
    // Store corresponding type in displayType
    char displayType;
    if (type == CLUBS)
        displayType = 'C';
    else if (type == DIAMONDS)
        displayType = 'D';
    else if (type == HEARTS)
        displayType = 'H';
    else
        displayType = 'S';

    // Get the corresponding rank in type int and output
    int displayRank = rank;                         
    if (rank == 11)
        printf("J%c ", displayType);
    else if (rank == 12)
        printf("Q%c ", displayType);
    else if (rank == 13)
        printf("K%c ", displayType);
    else
        printf("%d%c ", displayRank, displayType);
}

/*  The Hand class contains a vector of cards
 *  which indicates what cards a player has in
 *  its hands.
 */
class Hand
{
private:
    vector<Card> cards;

public:
    Hand();
    ~Hand();
    void add(Card *card);
    void clear();
    int getTotal();
    void displayHand();
};

Hand::Hand()
{
    // nothing
}

Hand::~Hand()
{
    // nothing to add here
}

/*  This function adds a card to the hand.
 *  by pushing it onto the vector of cards.
 *  This is used in the deal function in 
 *  the Deck class.
 */
void Hand::add(Card *card)
{
    cards.push_back(*card);
}

/*  This function resets player's hand
 *  so that they can replay the game.
 */
void Hand::clear()
{
    this->cards.clear();
}

/*  This function return's the hand's total
 *  worth by computing the sum of all the cards
 *  in the player's hand. By the Blackjack game rules,
 *  an Ace can be worth 1 or 11 points, whichever is
 *  convenient for the player. From getValue() in Card
 *  class, all Aces are worth 11 by default and so
 *  in this function it will decrement the total value
 *  by 10 for each ace if hand bursts.
 */
int Hand::getTotal()
{
    int numAce = 0;
    int total = 0;
    // Get temporary total, without taking into account of aces
    for (Card c : cards)
    {
        int curr = c.getValue();
        if (curr == 11)
            numAce++;
        total += curr;
    }

    // Take into account number of aces and get total when bursted
    if (total > 21)
    {
        while (total > 21 && numAce-- > 0)
            total -= 10;
    }
    return total;
}

void Hand::displayHand()
{
    // Outputs all cards in hand
    for (Card c : cards)
        c.displayCard();
}

class Deck
{
private:
    vector<Card> deck;

public:
    Deck();
    ~Deck();
    void populate();
    void shuffle();
    void deal(Hand *aHand);
};

Deck::Deck()
{
    // nothing 
}

Deck::~Deck()
{
    // nothing 
}

void Deck::populate()
{
    deck.clear();                                           // empty current deck
    for (unsigned suit = CLUBS; suit <= SPADES; suit++) {   // iterate through all suits
        for (unsigned num = ACE; num <= KING; num++) {      // iterate through all ranks
            Card c = Card(Rank(num), Type(suit));
            deck.push_back(c);                              // add every card to vector
        }
    }
}

void Deck::shuffle()
{
    // Shuffle deck using time as seed
    if (deck.empty())
        return;
    default_random_engine e(chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(begin(deck), end(deck), e);
}

void Deck::deal(Hand *aHand)
{
    // Take last card from deck and add to hand
    Card toDeal = deck.back();
    deck.pop_back();
    aHand->add(&toDeal);
}

class AbstractPlayer
{
protected:
    Hand *hand;

public:
    AbstractPlayer();
    ~AbstractPlayer();
    bool isBusted();
};

AbstractPlayer::AbstractPlayer()
{
    hand = new Hand();
}

AbstractPlayer::~AbstractPlayer()
{
    delete this->hand;
}

bool AbstractPlayer::isBusted()
{
    return (this->hand->getTotal() > 21);
}

class CasinoPlayer: public AbstractPlayer
{
public:
    CasinoPlayer();
    ~CasinoPlayer();
    Hand* getHand();
};

CasinoPlayer::CasinoPlayer()
{
    // nothing
}

CasinoPlayer::~CasinoPlayer()
{
    // nothing
}

Hand* CasinoPlayer::getHand()
{
    return this->hand;
}

class HumanPlayer: public AbstractPlayer
{
public:
    HumanPlayer();
    ~HumanPlayer();
    bool isDrawing();
    void announce(CasinoPlayer *casino);
    Hand* getHand();
};

HumanPlayer::HumanPlayer()
{
    // nothing
}

HumanPlayer::~HumanPlayer()
{
    // nothing
}

bool HumanPlayer::isDrawing()
{
    // Take user input to check if user wants to draw
    printf("Do you want to draw? (y/n): ");
    char answer = '!';          // initialize to random character
    cin >> answer;
    if (tolower(answer) == 'y')
        return true;
    else
        return false;
}

void HumanPlayer::announce(CasinoPlayer *casino)
{
    int casinoTotal = casino->getHand()->getTotal();
    int humanTotal = hand->getTotal();
    if (isBusted())
        printf("Player busts.\nCasino wins.\n\n");
    else if (casino->isBusted())
        printf("Casino busts.\nPlayer wins.\n\n");
    else if (casinoTotal > humanTotal)
        printf("Casino wins.\n\n");
    else if (humanTotal > casinoTotal)
        printf("Player wins.\n\n");
    else
        printf("Push: No one wins.\n\n");
}

Hand* HumanPlayer::getHand()
{
    return hand;
}

class BlackJackGame
{
private:
    Deck *m_deck;
    CasinoPlayer *m_casino;
    HumanPlayer *m_user;

public:
    BlackJackGame();
    ~BlackJackGame();
    void reset();
    void play();
};

BlackJackGame::BlackJackGame()
{
    m_deck = new Deck();
    m_casino = new CasinoPlayer();
    m_user = new HumanPlayer();
}

BlackJackGame::~BlackJackGame()
{
    delete this->m_deck;
    delete this->m_casino;
    delete this->m_user;
}

void BlackJackGame::reset()
{
    Hand *casino_hand = m_casino->getHand();
    Hand *user_hand = m_user->getHand();
    casino_hand->clear();
    user_hand->clear();
}

void BlackJackGame::play()
{
    reset();
    // Prepare deck and shuffle
    m_deck->populate();
    m_deck->shuffle();

    // Initialize casino player card deals
    Hand *casino_hand = m_casino->getHand();
    m_deck->deal(casino_hand);
    printf("Casino: ");
    casino_hand->displayHand();
    printf("[%d]\n", casino_hand->getTotal());

    // Initialize user card deals
    Hand *user_hand = m_user->getHand();
    m_deck->deal(user_hand);
    m_deck->deal(user_hand);
    printf("Player: ");
    user_hand->displayHand();
    printf("[%d]\n", user_hand->getTotal());

    // Deal cards to users
    bool user_busted = false;                   // bool used to see if casino needs to play
    while (m_user->isDrawing())
    {
        // Deal card
        m_deck->deal(user_hand);
        user_hand->displayHand();
        printf("[%d]\n", user_hand->getTotal());

        // Stop dealing card when user busts
        if (m_user->isBusted())
        {
            m_user->announce(m_casino);
            user_busted = true;
            break;
        }
        
    }

    // Deal cards to casino player as long as it's less than user's
    while (!user_busted && casino_hand->getTotal() != 21)
    {
        // Stop dealing when casino wins
        if (casino_hand->getTotal() > user_hand->getTotal())
            break;
        // Deal another card if no bust
        if (!(m_casino->isBusted()))
            m_deck->deal(casino_hand);
        // Stop dealing cards when bust
        casino_hand->displayHand();
        printf("[%d]\n", casino_hand->getTotal());
    }
    // Announce winner
    if (!user_busted)
        m_user->announce(m_casino);
}

int main()
{
    printf("\nWelcome to the blackjack table\n\n");
    BlackJackGame game;
    while (true)
    {
        game.play();
        printf("Would you like to play another round? (y/n): ");
        char answer = '!';          // initialize to random character
        cin >> answer;
        if (tolower(answer) != 'y')
            break;
    }
    printf("Game over! Thank you for visiting the Blackjack table.");
    return 0;
}
