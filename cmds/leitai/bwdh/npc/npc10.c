// modified by explorer, 3/9/97
inherit NPC;
void create()
{
        set_name("С���߹�", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "��ָ��ؤ");
        set("gender", "����");
        set("age", 75);
        set("long", 
                "������ؤ���ʮ���ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
        set("attitude", "friendly");
        set("str", 40);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);    
        set("unique", 1);
         
        set_skill("force", 100);             // �����ڹ�
        set_skill("huntian-qigong", 100);    // ��������
        set_skill("strike", 100);            // �����Ʒ�
        set_skill("xianglong-zhang", 100);   // ����ʮ����
        set_skill("dodge", 100);             // ��������
        set_skill("xiaoyaoyou", 100);        // ��ң��
        set_skill("parry", 100);             // �����м�
        set_skill("stick", 100);             // ��������
        set_skill("dagou-bang", 100);        // �򹷰���
        set_skill("begging", 100);           // �л�����
        set_skill("checking", 100);          // ����;˵
        set_skill("bangjue",100);            // ����  

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        prepare_skill("strike", "xianglong-zhang");  

        create_family("ؤ��", 17, "����");
        setup();

        carry_object(__DIR__"obj/yzb")->wield();
        carry_object("/d/gb/npc/obj/jiaohuaji");
        carry_object("/d/gb/npc/obj/bainayi")->wear();
        carry_object("/d/gb/npc/obj/gb_budai10")->wear();
        carry_object("/clone/medicine/badan");
}
