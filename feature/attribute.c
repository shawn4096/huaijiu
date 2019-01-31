// attribute.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <dbase.h>
#include <skill.h>

varargs int query_str(int post)
{
	int improve, tmp;

	improve = query_skill("claw", 1) / 10;
	tmp = query_skill("cuff", 1) / 10;
	if (tmp > improve) improve = tmp;
	tmp = query_skill("finger", 1) / 10;
	if (tmp > improve) improve = tmp;
	tmp = query_skill("hand", 1) / 10;
	if (tmp > improve) improve = tmp;
	tmp = query_skill("strike", 1) / 10;
	if (tmp > improve) improve = tmp;
	tmp = query_skill("leg", 1) / 10;
	if (tmp > improve) improve = tmp;
	tmp = query_skill("unarmed", 1) / 10;
	if (tmp > improve) improve = tmp;

	return query("str") + (post?0:query_temp("apply/strength")) + improve;
}

varargs int query_int(int post)
{
	return query("int") + (post?0:query_temp("apply/intelligence")) + query_skill("literate", 1) / 10;
}

varargs int query_con(int post)
{
	return query("con") + (post?0:query_temp("apply/constitution")) + query_skill("force", 1) / 10;
}

varargs int query_dex(int post)
{
	return query("dex") + (post?0:query_temp("apply/dexerity")) +	// should be dexterity, damn it. YUJ@SJ
		query_skill("dodge", 1) / 10;
}

varargs int query_kar(int post)
{
	return query("kar") + (post?0:query_temp("apply/karma"));
}

varargs int query_per(int post)
{
	return query("per") + (post?0:query_temp("apply/personality"))
		+ (query("gender") == "����"?0:query_skill("beauty", 1) / 20)
		- query("age")/10 + 2; // 20 �Ժ�ſ�ʼ��per, ���Լ�2.
}
