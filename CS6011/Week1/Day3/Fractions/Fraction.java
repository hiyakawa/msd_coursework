import java.util.ArrayList;
import java.util.Collections;

public class Fraction implements Comparable<Fraction> {
    private long numerator_;
    private long denominator_;

    public Fraction() {
        numerator_ = 0;
        denominator_ = 1;
    }

    public Fraction(long n, long d) throws IllegalArgumentException {
        // if denominator is 0, throw an exception
        if (d == 0) {
            throw new IllegalArgumentException("The denominator is zero!");
        }
        if (n == 0) {
            numerator_ = 0;
            denominator_ = 1;
        }
        else {
            numerator_ = n;
            denominator_ = d;

            long gcd = GCD();
            numerator_ /= gcd;
            denominator_ /= gcd;

            // the negative sign should always be on the numerator
            if (denominator_ < 0) {
                numerator_ = - numerator_;
                denominator_ = - denominator_;
            }
        }
    }

    private long GCD() {
        long gcd = numerator_;
        long remainder = denominator_;

        while (remainder != 0) {
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }

        return gcd;
    }

    private void reduce() {
        // if denominator is 0, throw an exception
        if (denominator_ == 0) {
            throw new IllegalArgumentException("The denominator is zero!");
        }

        long gcd = GCD();
        numerator_ /= gcd;
        denominator_ /= gcd;

        // the negative sign should always be on the numerator
        if (denominator_ < 0) {
            numerator_ = - numerator_;
            denominator_ = - denominator_;
        }
    }

    public Fraction plus(Fraction rhs) {
        Fraction temp = new Fraction();
        temp.numerator_ = numerator_ * rhs.denominator_ + denominator_ * rhs.numerator_;
        temp.denominator_ = denominator_ * rhs.denominator_;
        temp.reduce();

        return temp;
    }

    public Fraction minus(Fraction rhs) {
        Fraction temp = new Fraction();
        temp.numerator_ = numerator_ * rhs.denominator_ - denominator_ * rhs.numerator_;
        temp.denominator_ = denominator_ * rhs.denominator_;
        temp.reduce();

        return temp;
    }

    public Fraction times(Fraction rhs) {
        Fraction temp = new Fraction();
        temp.numerator_ = numerator_ * rhs.numerator_;
        temp.denominator_ = denominator_ * rhs.denominator_;
        temp.reduce();

        return temp;
    }

    public Fraction dividedBy(Fraction rhs) {
        Fraction temp = new Fraction();
        temp.numerator_ = numerator_ * rhs.denominator_;
        temp.denominator_ = denominator_ * rhs.numerator_;
        temp.reduce();

        return temp;
    }

    public Fraction reciprocal() {
        Fraction temp = new Fraction();
        long temp_numerator = numerator_;
        temp.numerator_ = denominator_;
        temp.denominator_ = temp_numerator;
        temp.reduce();

        return temp;
    }

    @Override
    public String toString() {
        this.reduce();
        String strFraction = numerator_ + "/" + denominator_;
        return strFraction;
    }

    public double toDouble() {
        double dblFraction = 1.0 * numerator_ / denominator_;
        return dblFraction;
    }

    @Override
    public int compareTo(Fraction rhs) {
        if (numerator_ * rhs.denominator_ > denominator_ * rhs.numerator_) {
            return 1;
        }
        else if (numerator_ * rhs.denominator_ == denominator_ * rhs.numerator_) {
            return 0;
        }
        return -1;
    }
}

class Main {
    public static void main(String[] args) {
        // day 6 updated: Lab - Sorting Fractions
        Fraction f1 = new Fraction(6, -12);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = new Fraction(-1, 6);
        Fraction f4 = new Fraction(5, 6);

        ArrayList<Fraction> fractions = new ArrayList<>();
        fractions.add(f1);
        fractions.add(f2);
        fractions.add(f3);
        fractions.add(f4);

        Collections.sort(fractions);
        for (Fraction f : fractions) {
            System.out.println(f.toString());
        }
    }
}