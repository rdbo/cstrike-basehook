class Vector2D;

class Vector {
  public:
    vec_t x;
    vec_t y;
    vec_t z;

    Vector(void);
    Vector(float, float, float);
    Vector(const Vector &);
    Vector(float *);
    Vector operator-(void) const;
    Vector operator-(const Vector &) const;
    int operator==(const Vector &) const;
    int operator!=(const Vector &) const;
    Vector operator+(const Vector &) const;
    Vector operator*(float) const;
    Vector operator/(float) const;
    void CopyToArray(float *) const;
    float Length(void) const;
    float LengthSquared(void) const;
    operator float*(void);
    operator float const*(void) const;
    Vector Normalize(void) const;
    Vector2D Make2D(void) const;
    float Length2D(void) const;
    bool IsLengthLessThan(float) const;
    bool IsLengthGreaterThan(float) const;
    float NormalizeInPlace(void);
    bool IsZero(float);
};