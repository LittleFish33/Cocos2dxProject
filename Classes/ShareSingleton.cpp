class ShareSingleton
{
private:
	ShareSingleton(){}
	static ShareSingleton* Instance;
public:

	bool opponentFlipx = false;

	static ShareSingleton* GetInstance()
	{
		if (Instance == nullptr) {
			Instance = new ShareSingleton();
		}
		return Instance;
	}
};