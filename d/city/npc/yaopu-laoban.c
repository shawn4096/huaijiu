// yaopu-laoban.c ҩ���ϰ�
// by shang 97/6

inherit NPC;
inherit F_DEALER;

int ask_book();
void create()
{
	set_name("ҩ���ϰ�", ({ "yaopu laoban", "laoban", "boss" }));
	set("gender", "����");
	set("long", "һλ������ҩ���ϰ�, ��Ӫ���洫�����̡�\n");
	set("age", 65);

	set("int", 20);
	
	set("qi", 300);
	set("max_qi", 300);
	set("jing", 300);
	set("max_jing", 300);
	set("shen_type", 1);

	set("combat_exp", 5000);
	set("attitude", "heroism");

	set_skill("unarmed", 40);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage", 20);

	set("vendor_goods", ({
	}));
       set("inquiry", ([
       "ҽ��" : (: ask_book :),
       "ҩ��" : (: ask_book :),
    ]));

	setup();
	add_money("silver", 15);
}

void init()
{
//add_action("do_buy", "buy");
}
int ask_book()
{
  command("sigh");
  command("say ����˵�Ǳ�[�ƽ𾵸�����]�ɣ�ǰ���컹���������ģ���֪�����ĸ��һ�\n"
+"˳��ǣ���͵���ˣ�������������ͷ����\n");
  this_player()->set_temp("marks/m-book4", 1);
return 1;
}
