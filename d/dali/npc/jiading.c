// jiading.c �Ҷ�

inherit NPC;

void create()
{
	set_name("�Ҷ�", ({ "jia ding", "jia" }));
	set("gender", "����");
	set("age", 35);

	set("combat_exp", 4000);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_temp("apply/attack",  10);
        set_temp("apply/defense", 10);
	set("shen_type", -1);
	setup();
	carry_object("/clone/weapon/changjian2")->wield();
	carry_object("/clone/armor/cloth")->wear();
}
