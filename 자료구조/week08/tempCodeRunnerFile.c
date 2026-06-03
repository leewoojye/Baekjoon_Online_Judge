    TreeNode n_d = { 'D', NULL, NULL, TRUE };
    TreeNode n_e = { 'E', NULL, NULL, TRUE };
    TreeNode n_f = { 'F', NULL, NULL, TRUE };
    TreeNode n_b = { 'B', &n_d, &n_e, FALSE };
    TreeNode n_c = { 'C', &n_f, NULL, TRUE };
    TreeNode n_a = { 'A', &n_b, &n_c, FALSE };