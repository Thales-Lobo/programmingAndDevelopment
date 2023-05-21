#include <iostream>
#include <string>
#include <utility>

class Number {
public:
    // Constructeur par défaut
    Number( unsigned long l ) {
        first_ = new Digit(l);
    }
    // Constructeur de copie
    Number(const Number &num){
        first_ = new Digit(*num.first_);
    }
    // Constructeur de string
    Number( std::string s ){
        first_ = new Digit(s);
    }
    // Destructeur
    ~Number() {
        delete first_;
    }
    // Opérateur d'affectation
    Number &operator = (const Number &num){
        delete first_;
        first_ = new Digit(*num.first_);
        return *this;
    }

    void print( std::ostream & out ) const {
        first_->print(out);
    }

    void add( unsigned int i ){
        first_->add(i);
    }

    void multiply( unsigned int i ){
        first_->multiply(i, 0);
    }

private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit * next_;

        // Constructeur par défaut
        Digit(unsigned long l){
            digit_ = l%number_base;

            if(l < number_base){
                next_ = nullptr;
            }
            else{
                next_ = new Digit(l/number_base);
            }
        }

        // Constructeur de copie
        Digit(const Digit &dig){
            digit_ = dig.digit_;

            if(dig.next_ != nullptr){
                next_ = new Digit(*dig.next_);
            }
            else{
                next_ = nullptr;
            }
        }

        // Constructeur de string
        Digit(std::string  &s){
            digit_ = static_cast< unsigned int >( s.at(s.length()-1) - '0' );
            s.pop_back();

            if(s.length() == 0){
                next_ = nullptr;
            }
            else{
                next_ = new Digit(s);
            }
        }

        // Destructeur
        ~Digit(){
            if(next_ != nullptr){
                delete next_;
            }
        }

        void print( std::ostream & out ) const {
            if(next_ != nullptr){
                next_->print(out);
            }
                out << digit_;
        }

        void add( unsigned int i ){
            unsigned int carry = (static_cast<unsigned long>(digit_) + i)/number_base;
            digit_ = (static_cast<unsigned long>(digit_) + i)%number_base;

            if(carry != 0 && next_ == nullptr){
                next_ = new Digit(carry);
            }
            else if(carry != 0){
                next_->add(carry);
            }
        }

        void multiply( unsigned int i, unsigned int carry){
            unsigned long temp = (static_cast<unsigned long>(digit_) * i) + carry;
            carry = temp/number_base;
            digit_ = temp%number_base;

            if(next_ == nullptr){
                next_ = new Digit(carry);
            }
            else{
                next_->multiply(i, carry);
            }
        }
    };
    Digit * first_;
};

inline std::ostream & operator<<( std::ostream & out, const Number & n )
{
    n.print( out );
    return out;
}

int main(){
    Number n{ "12345" };
    //str.pop_back();
    //std::cout << str << std::endl;
}