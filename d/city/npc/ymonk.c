//  monk.c

inherit NPC;

void create()
{
	set_name("С����", ({ "young monk","monk" }) );
	set("class", "bonze");
	set("gender", "����");
	set("age", 15);
	set("long",
		"�������޳��������յ�Сͽ�ܡ���������Ĵ�ɨ��Ժ��\n");
	set("title", "������С����");
	set("combat_exp", 9000);
	set("shen_type", 1);
	set("attitude", "friendly");
	set("inquiry", ([
	"mud" :"����Ǹով����˿�籩���ķ�������ɵ�ȫ�£ͣգģ�",
	]) );
	setup();

	set("apply/attack", 60);
	set("apply/defense", 60);

	set_skill("unarmed", 30);
	set_skill("sword", 40);
	set_skill("parry", 30);
	set_skill("dodge", 36);
	setup();

	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 1);
}       
