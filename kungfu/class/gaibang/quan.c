// NPC: quan.c ȫ����
// Modify By Looklove 2000/10/18

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("ȫ����", ({"quan guanqing", "quan" }));
	set("title", "ؤ����Ƿֶ����");
	set("nickname", "ʮ�����");
	set("gender", "����");
	set("age", 35);
	set("long", "���ǰ˴��������ƹܴ��Ƿֶ棬Ϊ�����Ƕ�ı���书��ǿ��\n");
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 25);
	set("int", 35);
	set("con", 20);
	set("dex", 25);

	set("qi", 1200);
	set("max_qi", 1200);
	set("jing", 900);
	set("max_jing", 900);
	set("neili", 1600);
	set("max_neili", 1600);
	set("jiali", 100);
	
	set("combat_exp", 400000);
	
	set_skill("force", 130); // �����ڹ�
	set_skill("huntian-qigong", 130); // ��������
	set_skill("strike", 130); // ����ȭ��
	set_skill("dodge", 130); // ��������
        set_skill("xiaoyaoyou", 120); // ǧ������ 
	set_skill("parry", 120); // �����м�
        set_skill("lianhua-zhang", 130);
	
	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("strike", "lianhua-zhang");
	map_skill("parry", "lianhua-zhang");
	prepare_skill("strike", "lianhua-ang");
	
	create_family("ؤ��", 19, "�˴�����");
	set("chat_chance", 2);
        set("chat_msg", ({
            "ȫ�������һ��������ׯ��С�Ӷ���֪����ȥ�ˣ���СС���飬��ô���ˣ���û������\n",
	}) );	

	set("inquiry", ([
		"ؤ��" : "����ؤ�������µ�һ��\n",
		"�Ƿ�" : "�ٺ٣���������Ƿ��ˡ�\n",
	]));
	setup();
	carry_object(__DIR__"obj/gb_budai8")->wear();
	carry_object(__DIR__"obj/bainayi")->wear();
}
void attempt_apprentice(object ob)
{
	if ((int)ob->query_int() <=20	) {
		command("say Ҫ����ұ��빻����" + 
		RANK_D->query_respect(ob) + 
		"������̫�ͣ��ҿɲ���Ҫ��������\n");
		return;
	}

        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
	}
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ���������㣬�����ǰ������ϡ�");
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        if (ob->query("family/family_name")!= "ؤ��"){
        	ob->set("gb_bags", 1);
        }
        ob->set("title",sprintf("ؤ����Ƿֶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","���Ƿֶ�");
        ob->set("gb/alloted",1);
	ob->set("class","beggar");
}
