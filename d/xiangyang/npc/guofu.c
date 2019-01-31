inherit NPC;
void create()
{
        set_name("��ܽ", ({"guo fu", "guo", "fu"}));
        set("long","�����ǹ��������ص�Ů����ܽ��ؤ��Ү����������ˡ�\n");

        set("gender", "Ů��");
        set("attitude", "peaceful");
        set("unique", 1);

        set("age", 25);
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        set("max_qi", 5500);
        set("max_jing", 5500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("max_jingli", 5500);
        set("eff_jingli", 5500);
        set("jiali", 50);
        set("combat_exp", 1200000);
        set("chat_chance_combat", 40);

        set_skill("dacheng-fofa", 165);
        set_skill("linji-jianzhen", 180);
        set_skill("linji-zhuang", 165);
        set_skill("jieshou-jiushi", 165);
        set_skill("huifeng-jian", 165);
        set_skill("sixiang-zhang", 165);
        set_skill("yanxing-daofa", 165);
        set_skill("hand", 165);
        set_skill("lanhua-shou",180);
        set_skill("literate", 165);
        set_skill("strike", 165);
        set_skill("sword", 165);
        set_skill("blade", 165);
        set_skill("parry", 165);
        set_skill("dodge", 165);
        set_skill("force", 165);
        set_skill("anying-fuxiang", 165);

        map_skill("force", "linji-zhuang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-daofa");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "sixiang-zhang");
        map_skill("hand", "lanhua-shou");

        prepare_skill("hand", "lanhua-shou");

        create_family("ؤ��", 20, "��������");

        setup();
        carry_object("/d/emei/obj/changjian")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}
