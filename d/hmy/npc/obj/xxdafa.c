// force_book.c �ڹ��ķ�

inherit ITEM;

void create()
{
	set_name("���Ǵ�", ({ "xxdafa book","book"}));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����װ�飬������������Ļ��˲��ٴ������ŵ����ơ�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"xxdafa",	// name of the skill
			"exp_required":	10000,	// minimum combat experience required
			"jing_cost":	60,	// jing cost every time study this
			"difficulty":	10,	// the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn

		]) );
	}
}
