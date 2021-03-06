﻿using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Qml.Net.Internal.Qml
{
    internal class NetTestHelper
    {
        public static void RunQml(QQmlApplicationEngine qmlEngine, string qml)
        {
            Interop.NetTestHelper.RunQml(qmlEngine.Handle, qml);
        }
    }

    internal class NetTestHelperInterop
    {
        [NativeSymbol(Entrypoint = "net_test_helper_runQml")]
        public RunQmlDel RunQml { get; set; }

        [SuppressUnmanagedCodeSecurity]
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void RunQmlDel(IntPtr qmlEngine, [MarshalAs(UnmanagedType.LPWStr)]string qml);
    }
}