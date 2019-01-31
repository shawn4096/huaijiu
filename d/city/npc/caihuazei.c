// /d/city/npc/caihuazei.c

inherit NPC;

void create()
{
	set_name("�ɻ���", ({"caihua zei", "caihua", "zei"}));
	set("long", "����һ��ר�ż�������Ů�ӵĲɻ�����\n");

	set("gender", "����");
	set("attitude", "heroism");

	set("age", 35);
	set("shen_type", -1);
	set("shen", -100000);
	set("str", 26);
	set("int", 23);
	set("con", 25);
	set("dex", 26);
	set("max_qi", 1500);
	set("max_jing", 1000);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiaji", 80);
	set("combat_exp", 220000);

	set_skill("force", 100);
	set_skill("dodge", 90);
	set_skill("unarmed", 90);
	set_skill("parry", 100);

	setup();
        add_money("gold", random(1));
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob = this_player();

	if (ob->query("gender") == "Ů��" && ob->query("per") > 20) {
		remove_call_out("do_greet");
		call_out("do_greet", 1, ob);
	}
}

void do_greet(object ob)
{
	if (present(ob, environment())) {
		tell_object(ob, "�ɻ���������Ц������" + RANK_D->query_respect(ob) + "���ǲ��Ǻܼ�įѽ����\n");
	}
}

