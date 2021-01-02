class CUnifiedSignals {
  private:
    int m_flSignal;
    int m_flState;

  public:
    CUnifiedSignals(void);
    int Update(void);
    void Signal(int);
    int GetState(void);
};