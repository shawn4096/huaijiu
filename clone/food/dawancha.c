inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("�����",({"tea", "cha", "dawan cha"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������裬���Ƶ�ð������������\n");
		set("unit", "��");
		set("value", 0);
        }
	set("liquid", ([
		"type": "water",
		"name": "��ˮ",
		"remaining": 3,
		"drunk_apply": 15,
	]));
}

