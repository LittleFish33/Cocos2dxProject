class ShareSingleton
{
private:
	ShareSingleton(){}
	static ShareSingleton* Instance;
public:

	bool opponentFlipx = false;
	int selectedBackground = 1;
	bool controlVoice = true;
	static ShareSingleton* GetInstance()
	{
		if (Instance == nullptr) {
			Instance = new ShareSingleton();
		}
		return Instance;
	}
};