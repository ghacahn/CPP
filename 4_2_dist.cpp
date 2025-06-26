class Distance
{
private:
	int metr;
	float cent;
public:
	Distance() : metr(0), cent(0.0)
	{}
	Distance(int m, float c) : metr(m), cent(c)
	{}
	Distance(float met)
	{
		metr = (int)met;
		cent = (met - float(metr)) * 100;
	}
	operator float() const
	{
		return metr + cent / 100.0;
	}
	Distance operator +(Distance);
	Distance operator -(Distance);
	Distance operator *(Distance);
	bool operator <(const Distance) const;
	bool operator >(const Distance) const;
	bool operator ==(const Distance) const;
	Distance operator +=(Distance);
	void vivod(int);
};

Distance Distance::operator+(Distance dist1)
{
	Distance dist2(metr, cent), dist3;
	float f1 = dist1, f2 = dist2, f3;
	f3 = f1 + f2;
	dist3 = f3;
	return Distance(dist3);
}
Distance Distance::operator-(Distance dist1)
{
	Distance dist2(metr, cent), dist3;
	float f1 = dist1, f2 = dist2, f3;
	f3 = f2 - f1;
	dist3 = f3;
	return Distance(dist3);
}
Distance Distance::operator*(Distance dist1)
{
	Distance dist2(metr, cent), dist3;
	float f1 = dist1, f2 = dist2, f3;
	f3 = f2 * f1;
	dist3 = f3;
	return Distance(dist3);
}
bool Distance::operator<(const Distance dist2) const
{
	Distance dist1(metr, cent);
	float f1 = dist1, f2 = dist2;
	return (f1 < f2) ? true : false;
}
bool Distance::operator>(const Distance dist2) const
{
	Distance dist1(metr, cent);
	float f1 = dist1, f2 = dist2;
	return (f1 > f2) ? true : false;
}
bool Distance::operator==(const Distance dist2) const
{
	Distance dist1(metr, cent);
	float f1 = dist1, f2 = dist2;
	return (f1 == f2) ? true : false;
}
Distance Distance::operator+=(Distance dist2)
{
	Distance dist1(metr, cent);
	float f1 = dist1, f2 = dist2;
	f1 = f1 + f2;
	dist1 = f1;
	metr = dist1.metr;
	cent = dist1.cent;
	return Distance(dist1);
}
void Distance::vivod(int n)
{
	cout << "dist" << n << " = " << metr << " м " << cent << " см " << endl;
}