// xiang.c ���
// Modify By Looklove 2000/10/21

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("���", ({"xiang zhanglao", "xiang" }));
	set("title", "ؤ�ﴫ������");
	set("gender", "����");
	set("age", 70);
	set("long", 
       		"����ؤ�ﴫ�����ϣ������վ��죬ר�Ÿ�����ڵ����Ǳ����书��\n");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 35);
	set("con", 20);
	set("dex", 30);

	set("qi", 1500);
	set("max_qi", 1500);
	set("jing", 900);
	set("max_jing", 900);
	set("neili", 1600);
	set("max_neili", 1600);
	set("jiali", 100);
	
	set("combat_exp", 1500000);
	
	set_skill("force", 170); // �����ڹ�
	set_skill("huntian-qigong", 180); // ��������
	set_skill("strike", 150); // ����ȭ��
	set_skill("dodge", 150); // ��������
        set_skill("xiaoyaoyou", 170); // ǧ������ 
	set_skill("parry", 170); // �����м�
        set_skill("sword",170);
        set_skill("blade",170);
        set_skill("liuhe-daofa",150);
        set_skill("hand",170);
        set_skill("suohou-shou",170);
	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
        map_skill("hand","suohou-shou");
	map_skill("parry", "suohou-shou");
	prepare_skill("hand", "suohou-shou");

	create_family("ؤ��", 18, "��ϯ����");
	set("inquiry", ([
		"ؤ��" : "����ؤ�������µ�һ��\n",
		"�Ƿ�" : "����һλ�˲���Ĵ�Ӣ�ۣ���ϧ�������ࡣ\n",
	]));
	setup();
	carry_object(__DIR__"obj/gb_budai9")->wear();
}
void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
	}
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }
        if((int)ob->query("combat_exp",1)<100000){
          	command("say ����书�������졣\n");
          	return;
         }

        if((int)ob->query_skill("huntian-qigong",1)<100){
           command("say ����������ؤ�����������Ĺ�����Դ����в�������\n");
           return;
	}
        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        
        command("recruit " + ob->query("id"));
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        ob->set("title",sprintf("ؤ���ܶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","�ܶ�");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
