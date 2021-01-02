class Vector2D {
  public:
    vec_t x;
    vec_t y;

    Vector2D(void);
    Vector2D(float, float);
    Vector2D operator+(const Vector2D &) const;
    Vector2D operator-(const Vector2D &) const;
    Vector2D operator*(float) const;
    Vector2D operator/(float) const;
    float Length(void) const;
    float LengthSquared(void) const;
    Vector2D Normalize(void) const;
    bool IsLengthLessThan(float) const;
    bool IsLengthGreaterThan(float) const;
    float NormalizeInPlace(void);
    bool IsZero(float);
};