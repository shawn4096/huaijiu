// pobudai.c �Ʋ���

#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;

void create()
{
	set_name("�Ʋ���", ({ "po budai", "budai","bian" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������������鲼�����������������\n");
		set("value", 10);
		set("material", "cloth");
		set("wield_msg", "$N�ӻ����ͳ�һ���Ʋ���ץ�����е�������\n");
		set("unwield_msg", "$N�����е�$n��һ�ۣ��Ž����\n");
        set("treasure",1);
	}
	init_whip(50);
	setup();
}
