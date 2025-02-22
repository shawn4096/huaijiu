// qi-changfa.c
// Modify By River 2000/03/03
inherit NPC;

void create()
{
        set_name("戚长发", ({ "qi changfa", "qi", "changfa"}) );
        set("title", "铁索横江" );
        set("gender", "男性" );
        set("age", 45);
        set("long", "这位先生站在那里，一副神秘莫测的样子。\n");
        set("combat_exp", 80000);
        set("unique", 1);
        set("attitude", "friendly");
        set("inquiry", ([                 
                "rumors" : "要想知道你今生的祸福荣辱，那就问我来算命吧。",
                "寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "算命" : "我的价钱最公道，不多不少，只要二两银子。"
        ]) );

        set("chat_chance", 3);
        set("chat_msg", ({
                "戚长发吆喝道：铁嘴神算，价钱公道，相资二两白银。\n",
                (: random_move :),
                "戚长发对你说道：客倌请留步，卜个吉凶如何？\n",
        }));
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

int accept_object(object who, object ob)
{
        int kar, per;

        if (ob->query("money_id") && ob->value() >= 200) 
        {
                message_vision("戚长发对着$N端详了一阵。\n", who);
                per = who->query("per");
                kar = who->query("kar");
                if (per > 25) {
                        write("戚长发景仰地说：“看" + RANK_D->query_respect(who) + "相貌堂堂，天庭饱满，地廓方圆，"); 
                        if (kar > 20) write("真乃富贵之象也！”\n");
                        else if (kar >= 17) write("一生运势平平，也算过得去了。”\n");
                        else if (kar >= 13) write("可惜冲撞了小人。”\n");
                        else write("不过你霉运当头，行事可要小心了！”\n");
                        return 1;
                }
                else if (per >= 20) {
                        write("戚长发清了清嗓子，说：“看" + RANK_D->query_respect(who) + "相貌属中上之资，"); 
                        if (kar > 20) write("一生大富大贵，子孙多多。”\n");
                        else if (kar >= 17) write("一生运势平平，也算过得去了。”\n");
                        else if (kar >= 13) write("就可惜冲撞了小人。”\n");
                        else write("不过你霉运当头，行事可要小心了！”\n");
                        return 1;
                }
                else if (per >= 15) {
                        write("戚长发有点勉强地说：“看" + RANK_D->query_respect(who) + "相貌平平，倒也还能算是中人之资，");
                        if (kar > 20) write("前生一定行了善事，一生大富大贵，子孙多多。”\n");
                        else if (kar >= 17) write("一生也就运势平平，只能算过得去。”\n");
                        else if (kar >= 13) write("就可惜冲撞了小人。”\n");
                        else write("你最近霉运当头，行事可要小心了！”\n");
                        return 1;
                }
                else {
                        write("戚长发很厌恶地说：“看" + RANK_D->query_respect(who) + "五官挪位，印堂发暗，");
                        if (kar > 20) write("不过你前生一定行了善事，一生大富大贵，子孙多多。”\n");
                        else if (kar >= 17) write("倒还有些运气，也算过得去了。”\n");
                        else if (kar >= 13) write("所以你就一生坎坷，多遇小人。”\n");
                        else write("活该倒霉，当有血光之灾！”\n");
                        return 1;
                }
        }
        return 0;
}

